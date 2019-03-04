#include <Windows.h>
#include <process.h>
#include <cstdio>
#include <vector>
#include <map>  //map the event handle and event name
#include <string>
#include <algorithm>

int main() {

	std::vector<HANDLE> hEvents;
	std::map<HANDLE, std::string> handleName;

	int cnt = 2;
	for (int i = 0; i < cnt; ++i) {
		std::string name("event" + std::to_string(i));
		HANDLE handle = CreateEvent(NULL, FALSE, TRUE, NULL);
		if (handle != NULL) {
			handleName.emplace(handle, name);
			hEvents.emplace_back(handle);
		}
	}


	for (int i = 0; i < 10; ++i) {
		DWORD r = WaitForMultipleObjectsEx(hEvents.size(), hEvents.data(), false, INFINITE, FALSE);
		if (r == WAIT_OBJECT_0) {

			auto it = handleName.find(hEvents[r]);
			if (it != handleName.cend()) {
				printf("%s signaled!\n", it->second.c_str());

				SetEvent(hEvents[r]);  //keep signal event 0 and event 1 will never got its signaled state reset 
				//because WaitForMultipleObjectsEx will check HANDLE ARRAY by order
				HANDLE h = hEvents[r];
				hEvents.erase(hEvents.cbegin() + r);
				hEvents.push_back(h);
			}

		}
		else if (r == WAIT_OBJECT_0 + 1) {
			printf("WAIT_OBJECT_0 +1\n");
		}
		else {

		}
	}

	//close handle
	auto it = std::cbegin(hEvents);
	while (it != std::cend(hEvents)) {
		CloseHandle(*it);
		++it;
	}

	getchar();
}