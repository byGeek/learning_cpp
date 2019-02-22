
#include <Windows.h>
#include <cstdio>
#include <process.h>
#include <assert.h>
//#include <WinSock2.h>

DWORD GetNumOfProcessors();

unsigned __stdcall ThreadFunc(PVOID params);

//HANDLE* g_threads;

int main() {

	enum {
		SRC_KEY =1,
		DST_KEY
	};

	//use CreateFile API to test 
	HANDLE hSrcFile = CreateFile("bigfile.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_ALWAYS/*OPEN_EXISTING*/, FILE_FLAG_OVERLAPPED /*| FILE_FLAG_DELETE_ON_CLOSE*/, NULL);  //set overlapped io and auto delete file if all related handle closed

	if (hSrcFile == INVALID_HANDLE_VALUE) {
		printf("CreateFile failed: %d\n", GetLastError());
		return -1;
	}

	LARGE_INTEGER liFileSize;
	liFileSize.QuadPart = 1024 * 1024 * 100;  //100MKb

	SetFilePointerEx(hSrcFile, liFileSize, NULL, FILE_BEGIN);
	SetEndOfFile(hSrcFile);

	liFileSize = { 0 };
	SetFilePointerEx(hSrcFile, liFileSize, NULL, FILE_BEGIN);  //set file pointer at beginning

	//create IO CompletionPort
	HANDLE hIOP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0/* 2 * GetNumOfProcessors()*/);

	if (hIOP == INVALID_HANDLE_VALUE) {
		printf("CreateIoCompletionPort failed: %d", GetLastError());
		return -1;
	}

	//associate IO completion port with hSrcFile
	if (hIOP != CreateIoCompletionPort(hSrcFile, hIOP, SRC_KEY, 0)) {
		printf("CreateIoCompletionPort failed: %d", GetLastError());
		return -1;
	}

	//get file size
	GetFileSizeEx(hSrcFile, &liFileSize);

	byte buf[1024];
	for(int i=0; i< 1024; ++i){
		buf[i] = i & ((1 << 8) - 1); //0~255
	}

	LARGE_INTEGER writen{ 0 };
	DWORD read = 0;
	DWORD per_writen = 0;
	BOOL ret = FALSE;

	OVERLAPPED overlapped = { 0 };
	ULONG_PTR key;


	//code asyncly but used as synchronous way
	while (writen.QuadPart < liFileSize.QuadPart) {
		//ret = WriteFileEx(hSrcFile, buf, 1024, &overlapped, NULL);
		ret = WriteFile(hSrcFile, buf, 1024, &per_writen, &overlapped);
		if (ret == 0) {
			if (GetLastError() != ERROR_IO_PENDING) {
				printf("WriteFile failed: %d\n", GetLastError());
				return -1;
			}
		}

		ret = GetQueuedCompletionStatus(hIOP, &per_writen, &key, (OVERLAPPED**)&overlapped, INFINITE);
		if (!ret) {
			printf("GetQueuedCompletionStatus failed: %d\n", GetLastError());
			return -1;
		}

		writen.QuadPart += 1024;
		overlapped.Offset = writen.QuadPart & 0xffffffff;  //set WriteFileEx offset in overlapped result
		overlapped.OffsetHigh = (writen.HighPart >> 32) & 0xffffffff;
	}



	SetFilePointerEx(hSrcFile, { 0 }, NULL, FILE_BEGIN);  //pinter start file pos

	//read and write to another file asyncly

	HANDLE hDstFile = CreateFile("copy.dat", GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_FLAG_OVERLAPPED,
		NULL);

	if (hDstFile == INVALID_HANDLE_VALUE) {
		printf("CreateFile copy.dat failed: %d", GetLastError());
		return -1;
	}

	//first set the final file size
	//because file system in windows is growing synchonously
	//if we want async WriteFile, we should first set the file size first
	SetFilePointer(hDstFile, liFileSize.QuadPart, NULL, FILE_BEGIN);  
	SetEndOfFile(hDstFile);

	//assotiate completion port with Dst file handle
	if (hIOP != CreateIoCompletionPort(hDstFile, hIOP, DST_KEY, 0)) {
		printf("CreateIoCompletionPort failed: %d", GetLastError());
		return -1;
	}

	int readInProgress = 0;
	int writeInProgress = 2;
	DWORD byteTransfered = 0;
	ULONG_PTR completionKey = 0;

	OVERLAPPED m_overlapped[2] = { 0,0 };
	LARGE_INTEGER totalWritenSize{ 0 };

	PostQueuedCompletionStatus(hIOP, 0, DST_KEY, &m_overlapped[0]);  //post a dummy IO packet to IO Quene
	PostQueuedCompletionStatus(hIOP, 0, DST_KEY, &m_overlapped[1]);  //post a dummy IO packet to IO Quene
	LPOVERLAPPED pOverlapped;

	byte buffer[1024];
	DWORD bytesWritten = 0;

	while (readInProgress > 0 || writeInProgress > 0) {
		//todo: see thread window to check threads number
		BOOL r = GetQueuedCompletionStatus(hIOP, &byteTransfered, &completionKey, &pOverlapped, INFINITE);
		if (r == FALSE) {
			printf("GetQueuedCompletionStatus failed: %d", GetLastError());
			assert(0);
		}

		switch (completionKey)
		{
		case 1:
			//from src file
			--readInProgress;
			printf("read\n");
			++writeInProgress;
			WriteFile(hDstFile, buffer, 1024, &bytesWritten, pOverlapped);  //write to the same offset which reads 

			break;
		case 2:
			--writeInProgress;
			if (totalWritenSize.QuadPart < liFileSize.QuadPart) {
				printf("write\n");
				//from dst file
				++readInProgress;

				pOverlapped->Offset = totalWritenSize.LowPart;
				pOverlapped->OffsetHigh = totalWritenSize.HighPart;

				ReadFile(hSrcFile, buffer, 1024, NULL, pOverlapped);  //read from src file
				totalWritenSize.QuadPart += 1024;
				

			}
			break;
		default:
			break;
		}


	}


	/*
	const DWORD numberOfThread = 5;
	HANDLE g_threads[numberOfThread];
	DWORD offsets[numberOfThread];

	//start 5 threads to write the file
	unsigned int threadid = 0;
	for (int i = 0; i < numberOfThread; ++i) {
		offsets[i] = i * liFileSize.QuadPart / numberOfThread;  //thread param should have valid address
		g_threads[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void *)offsets[i], 0, &threadid);
	}
	

	//wait for thread?
	DWORD ret = WaitForMultipleObjectsEx(numberOfThread, g_threads, TRUE, INFINITE, FALSE);

	//wait all true, then Wait function return ?
	if (ret >= WAIT_OBJECT_0 && ret <= WAIT_OBJECT_0 + numberOfThread) {

	}
	else
	{
		printf("WaitForMultipleObjectsEx failed: %d\n", GetLastError());
		return -1;
	}

	for (int i = 0; i < numberOfThread; ++i) {
		CloseHandle(g_threads[i]);
	}

	*/

	printf("done\n");
	CloseHandle(hSrcFile);
	CloseHandle(hDstFile);
	CloseHandle(hIOP);

	return 0;
}

DWORD GetNumOfProcessors() {
	SYSTEM_INFO info;
	GetSystemInfo(&info);

	return info.dwNumberOfProcessors;
}

unsigned __stdcall ThreadFunc(PVOID params) {
	DWORD offset = *reinterpret_cast<DWORD*>(params);
	return 0;

}
