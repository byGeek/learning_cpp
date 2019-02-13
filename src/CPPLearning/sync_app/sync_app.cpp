#include <Windows.h>
#include <process.h>
#include <cstdio>

CRITICAL_SECTION g_cs;
long g_sum = 0;
SRWLOCK g_srwlock;

void cleanup_resource() {
	DeleteCriticalSection(&g_cs);

	//there is no delete function to SRWLOCK


}

unsigned __stdcall thread_process(void *pvoid) {

	auto thread_id = GetCurrentThreadId();

	printf("thread id: %d start.\n", thread_id);

	EnterCriticalSection(&g_cs);

	for (int i = 0; i < 1000000; i++) {
		g_sum += i;
	}

	LeaveCriticalSection(&g_cs);

	printf("thread id: %d end.\n", thread_id);
	return 0;  //thread exit code
}

/*

Slim Read Write lock allow multiple reader to read from shared resources
but only one writer can write shared resource

*/


int g_data = 0;

unsigned __stdcall readclient_process(void *) {

	printf("read thread: %d\n", GetCurrentThreadId());

	AcquireSRWLockShared(&g_srwlock);

	//in here ,just read global variable and do nothing

	int read = g_data;

	for (int i = 0; i < 100000; i++) {
		read = g_data;
	}
	//printf("read g_data value: %d", read);


	ReleaseSRWLockShared(&g_srwlock);
	printf("read thread: %d end\n", GetCurrentThreadId());
	return 0;
}

unsigned __stdcall writeclient_process(void *) {

	printf("write thread: %d\n", GetCurrentThreadId());

	AcquireSRWLockExclusive(&g_srwlock);

	for (int i = 0; i < 100000; i++) {
		++g_data;
	}

	ReleaseSRWLockExclusive(&g_srwlock);

	printf("write thread: %d end.\n", GetCurrentThreadId());
	return 0;
}

void test_critical_section() {
	InitializeCriticalSection(&g_cs);

	HANDLE hthread[4];
	for (int i = 0; i < 4; i++) {
		hthread[i] = (HANDLE)_beginthreadex(NULL, 0, thread_process, NULL, 0, NULL);
	}

	WaitForMultipleObjects(4, hthread, true, INFINITE);

	for (int i = 0; i < 4; ++i) {
		CloseHandle(hthread[i]);
	}

}

void test_slimreadwritelock() {
	InitializeSRWLock(&g_srwlock);

	HANDLE hThreads[4];

	hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, writeclient_process, NULL, 0, NULL);
	hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, writeclient_process, NULL, 0, NULL);
	hThreads[2] = (HANDLE)_beginthreadex(NULL, 0, readclient_process, NULL, 0, NULL);
	hThreads[3] = (HANDLE)_beginthreadex(NULL, 0, readclient_process, NULL, 0, NULL);

	WaitForMultipleObjects(4, hThreads, true, INFINITE);
	printf("all done\n");

	for (int i = 0; i < 4; ++i) {
		CloseHandle(hThreads[i]);
	}

}

unsigned __stdcall dummy_thread(void *) {
	int sum = 0;
	for (int i = 0; i < 10000; i++) {
		sum += i;
	}

	return 0;
}

void test_thread() {
	unsigned int threadid;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, dummy_thread, NULL, 0, &threadid);


	
	WaitForSingleObject(hThread, INFINITE);
}

int main() {

	
	//test_slimreadwritelock();
	test_thread();


	getchar();
}