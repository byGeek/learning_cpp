//#include "stdafx.h"

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

int main() {
//#define
//	printf("%p\n", **************************************************************p);
//	return 0;

	std::string s("robert");
	test_var_args("%s age is %d", s.c_str(), 25);

	std::cout << std::endl;

	test_vaargs(1, 2, "robert");
	getchar();

}
