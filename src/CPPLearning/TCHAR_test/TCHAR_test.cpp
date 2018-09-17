// TCHAR_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

struct Person{
	std::string name;
	std::string place;

	std::string get_name() const{ return name; }
	std::string get_place() const{ return place; }
};




int _tmain(int argc, _TCHAR* argv[])
{
	Person *p = new Person();
	auto name = p->get_name();


}

