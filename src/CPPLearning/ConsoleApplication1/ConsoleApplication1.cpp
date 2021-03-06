#include "stdafx.h"

#include <stdio.h>
#include <string>
#include <stdarg.h>
#include <iostream>
#include <initializer_list>

void test_var_args(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buf[512];
	int len = vsprintf_s(buf, 512, format, args);
	//buf[len] = '\0';
	printf(buf);
	va_end(args);
}

template<typename T>
void test_vaargs(const T& t) {
	std::cout << t << std::endl;
}

template<typename T, typename... args>
void test_vaargs(const T& t, const args&... param) {
	std::cout << "sizeof...(args): " << sizeof...(args) << std::endl;
	std::cout << "sizeof...(param): " <<sizeof...(param) << std::endl;
	std::cout << "print: " << t << std::endl;
	test_vaargs(param...);
}

void test_var_args() {
	std::string s("robert");
	test_var_args("%s age is %d", s.c_str(), 25);

	std::cout << std::endl;

	test_vaargs(1, 2, "robert");
}

template<typename T>
int mysum(const T t) {
	return t;
}

template<typename T, typename... Args>
T mysum(T t, const Args... args) {
	t += mysum(args...);
	return t;
}

void test_mysum() {
	int sum = 0;
	sum = mysum(1, 2, 3);
}

//void test_myprint(const int&, const char[7]&, const double&)

void test_fun() {

	//#define
	//	printf("%p\n", **************************************************************p);
	//	return 0;
}

void test_addr_of() {
	auto value = ((sizeof(int) + sizeof(int) - 1) & ~(sizeof(int) - 1));
	std::cout << value << std::endl;
}

int sum_initializer_list(std::initializer_list<int> list) {
	auto beg = list.begin();
	auto sum = 0;
	for (; beg != list.end(); ++beg) {
		sum += *beg;
	}
	return sum;
}

void test_sum_initilizer_list() {
	sum_initializer_list({1,2,3});
}

template<typename T, typename... Args>
void foo(const T& t, const Args&... args);

int main() {
	test_mysum();
	getchar();

}
