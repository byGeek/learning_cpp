// MyLock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <atomic>

#include "MyLock.h"

static int g_num = 0;
static std::mutex g_mutex;


//static void printf_num(int num)
//{
//	std::cout << num << std::endl;
//}

template<typename T>
void simple_printf(const T& t) {
	std::cout << t << std::endl;
}

void dosomething(const std::string& msg)
{
	//MyLock mylock(&g_mutex);  //use mutex to sync
	std::lock_guard<std::mutex> lock(g_mutex);  //or use lock_guard to get exception safe

	simple_printf(msg + " start");
	for (int loop = 0;loop != 100;++loop) {
		std::ostringstream oss;
		oss << msg << " " << g_num;
		simple_printf(oss.str());
		++g_num;
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	simple_printf(msg + " end");
}

int main()
{
	std::thread t1(dosomething, "thread t1");
	std::thread t2(dosomething, "thread t2");

	t1.join();
	t2.join();

	simple_printf("all done!");

	std::cin.get();
    return 0;
}

