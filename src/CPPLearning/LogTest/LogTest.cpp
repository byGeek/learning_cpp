// LogTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <functional>

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

int main()
{
	//test();
	//test();
	//test1();
	test2();

	getchar();
    return 0;
}

