#include <Windows.h>
#include <process.h>
#include <cstdio>
#include <vector>

typedef struct {
	HANDLE hEvent;
	char tag[256];
} HANDLE_T;

int main() {

	std::vector<HANDLE> hEvents;

	HANDLE_T h1{ CreateEvent(NULL, FALSE, TRUE, NULL), "event1" };
	HANDLE_T h2{ CreateEvent(NULL, FALSE, TRUE, NULL), "event2" };

	hEvents.push_back(h1.hEvent);
	hEvents.push_back(h2.hEvent);

	for (int i = 0; i < 10; ++i) {
		DWORD r = WaitForMultipleObjectsEx(hEvents.size(), hEvents.data(), false, INFINITE, FALSE);
		if (r == WAIT_OBJECT_0) {
			printf("event 0\n");
			SetEvent(hEvents[0]);  //keep signal event 0 and event 1 will never got its signaled state reset 
			//because WaitForMultipleObjectsEx will check HANDLE ARRAY by order
			HANDLE h = hEvents[r];
			hEvents.erase(hEvents.cbegin() + r);
			hEvents.push_back(h);

		}
		else if (r == WAIT_OBJECT_0 + 1) {
			printf("event 1\n");
		}
		else {

		}
	}

	//close handle

	getchar();
}