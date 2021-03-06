// LogTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <functional>
#include <iostream>

#include "..\SingletonLog\log.h"

//use shared_ptr to release memory when done, assign a custom deletor
//std::shared_ptr<ILogger> ptr(GetLogger(), std::mem_fn(&ILogger::Release));


void test() {
	ILogger* logger = GetLogger();
	logger->Log("hello");
	delete logger;  //use delete to manual free memory, will call dtor
}

void test1() {
	ILoggerPtr ptrLogger(GetLogger(), std::mem_fn(&ILogger::Release));
	ptrLogger->Log("hello");
	//will autometically call release when function exit
}

void test2() {
	std::shared_ptr<ILogger> ptr(GetLogger());
	ptr->Log("hello");
	//shared_ptr will auto call dtor
}


void test3() {
	//ILoggerPtr logger(GetLogger(), Release);  //can not compile, why?
	//logger->Log("hello");

	//std::shared_ptr<ILogger> logger(GetLogger(), Release);

}

void test4() {
	std::shared_ptr<ILogger> logger(GetLogger(), std::mem_fn(&ILogger::Release));
	logger->Log("");
}

class A {

private:
	char* someMemory;
public:
	A() : someMemory(new char[10]) {};
	~A() { delete[] someMemory; }


};

void test_delete_call_destructor() {
	A* ptr = new A();
	delete ptr;
}

class dummy
{
private:
	int* data;

public:
	dummy() : data(new int[100]) {}
	~dummy() { delete[] data; }
	void release() {}
};

dummy* get_dummy() {
	return new dummy();
}

void release_dummy(dummy* ptr) {
}


void Release(dummy* ptr) {
	std::cout << "call release : not a memeber function!" << std::endl;
}


int main()
{
	//test();
	//test();
	//test1();
	test2();

	std::shared_ptr<dummy> ptr(new dummy(), release_dummy);
	std::shared_ptr<dummy> ptr2(new dummy(), std::mem_fn(&dummy::release));  //use std::mem_fn to turn a member function to a direct-callable object
	std::shared_ptr<dummy> ptr3(get_dummy(), Release);

	getchar();
    return 0;
}

