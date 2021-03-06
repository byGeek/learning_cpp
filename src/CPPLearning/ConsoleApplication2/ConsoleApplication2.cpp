// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <stdarg.h>
#include <iostream>

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

int test_sum(int num, ...) {
	va_list list;
	va_start(list, num);
	int i = 0;
	int sum = 0;
	while (i < num)
	{
		int value = va_arg(list, int);
		sum += value;
		++i;
	}
	va_end(list);
	return sum;
}

void test_sum_test()
{
	int sum = 0;
	sum = test_sum(1, 1);
	sum = test_sum(3, 1, 2, 3);
	sum = test_sum(3, 1, 2);
	sum = test_sum(4, 1, 2, 3, 4);
}

void test_var_args() {
	std::string s("robert");
	//const char* str = "robert";
	test_var_args("%s age is %d", s, 25);

	std::cout << std::endl;
}

void test_INTSIZEOF() {
	int size = 0;
	size = _INTSIZEOF("hello");
	size = _INTSIZEOF("h");
	size = sizeof("hello");
	size = sizeof("h");
}

int main()
{
	//test_var_args();
	test_INTSIZEOF();

	getchar();
    return 0;
}

