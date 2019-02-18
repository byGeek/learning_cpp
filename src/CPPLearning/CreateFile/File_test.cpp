//#include <fileapi.h>
#include <Windows.h>


int main() {

	HANDLE hFile = CreateFile("test.dat",
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS, 0, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		return -1;
	}

	LARGE_INTEGER li = { 0 };
	li.QuadPart = 1024;

	SetFilePointerEx(hFile, li, NULL, FILE_BEGIN);

	DWORD ret = SetEndOfFile(hFile);
	if (!ret) {
		return -1;  //failed
	}

	//FlushFileBuffers(hFile);

	CloseHandle(hFile);

}