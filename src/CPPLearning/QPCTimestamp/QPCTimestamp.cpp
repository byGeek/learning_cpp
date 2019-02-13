#include <Windows.h>
#include <iostream>
#include <thread>

class StopWatch {
public:
	StopWatch() {
		QueryPerformanceFrequency(&m_fre);
	}

	void Start() {
		QueryPerformanceCounter(&m_start);  //return the counter since the system is up
	}

	long long Ellapsed() const {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);

		return ((now.QuadPart - m_start.QuadPart) * 1000000 / m_fre.QuadPart);
	}

private:

	LARGE_INTEGER m_fre;
	LARGE_INTEGER m_start;
};


int main(int argc, char* args[]) {
	
	StopWatch sw;
	for (int i = 0; i < 10; i++) {
		sw.Start();

		Sleep(1000);

		auto ellaped = sw.Ellapsed();

		std::cout << "ellaped(ms):" << ellaped / 1000 << std::endl;
		std::cout << "ellaped(us):" << ellaped << std::endl;
	}
	
	std::cin.get();
}