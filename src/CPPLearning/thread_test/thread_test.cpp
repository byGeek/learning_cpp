#include <thread>
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include <memory>

#include "CDetached.h"


void simple_sleep(int seconds) {
	std::cout << "seconds: " << seconds << " \n";
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
	std::cout << std::this_thread::get_id() << " done!" << std::endl;
}


class foo {
public:
	void bar(int seconds) {
		simple_sleep(seconds);
	}

	void bar2() { std::cout << "nothing here, done" << std::endl; };
};

void use_detached_RAII() {
	CDetached set;
	set.creatDetachedThread(simple_sleep, 3);
	set.creatDetachedThread(simple_sleep, 4);
}

void use_thread_detach_manually() {
	std::thread t1(simple_sleep, 2);
	std::thread t2(simple_sleep, 5);
	std::thread t3(&foo::bar2, foo());  //memeber function first parameter is the THIS pointer, which here means foo object
	std::thread t4(&foo::bar, foo(), 2);



	int seconds = 5;
	std::thread t5([](int sec) {
		std::this_thread::sleep_for(std::chrono::seconds(sec));
		std::cout << std::this_thread::get_id() << "done!" << std::endl;
	}, 4);   //use lambda


	//use std::mem_fn to wrapper a member function , turn it to a function object
	std::thread t6(std::mem_fn(&foo::bar2), foo());  //still need to pass a foo object as argument



	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();
	t5.detach();
	t6.detach();
}


int main(int argc, char* arg[]) {

	use_detached_RAII();

	return 0;

}