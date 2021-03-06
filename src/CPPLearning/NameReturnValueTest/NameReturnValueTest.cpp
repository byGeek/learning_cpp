// NameReturnValueTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

#define DEFAULT_SIZE 100

void myprintf(const std::string& str) {
	std::cout << str << std::endl;
}

class Test
{
	friend Test foo();
public:
	Test() : data(new char[DEFAULT_SIZE])
	{ 
		myprintf("call ctor"); 
	}

	~Test() { 
		myprintf("call dtor"); 
		delete[] data; 
	}

	//need to provide a copy constructor because have char* dynamiclly allocatd memory

	//The rule of three

	Test(const Test& rhs) : data(new char[DEFAULT_SIZE])
	{
		myprintf("call copy ctor");
		memcpy_s(data, DEFAULT_SIZE, rhs.data, strlen(rhs.data) +1);
	}

	//copy assign operator
	Test& operator=(const Test& rhs)
	{
		myprintf("call copy assign operator");
		if (this != &rhs)  //self assign
		{
			char* temp = data;
			data = new char[DEFAULT_SIZE];
			memcpy_s(data, DEFAULT_SIZE, rhs.data, strlen(rhs.data) + 1);
			delete[] temp;
		}
		return *this;
	}

private:
	char* data;
};


//test name return value optimization
Test foo() {
	Test test;
	const std::string& data = "hello, world!";
	memcpy_s(test.data, DEFAULT_SIZE, data.c_str(), strlen(data.c_str()) +1);
	myprintf(test.data);

	return test;
}

void test_foo() {
	for (int i = 0; i < 10000; ++i) {
		Test t = foo();
	}
}


//run this program in Debug and Release mode
//you can see in release mode, the copy ctor is never called
//because of compiler's optimization
//Name return value(NRV)
void bar() {
	Test t1 = foo();
	t1 = t1;
	Test t2 = foo();
	t1 = t2;

}

int main()
{
	bar();

	std::cin.get();
}
