// ConstructorDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>

#include "HomeForSale.h"
#include "my_ctor.h"

void test_type_deduction() {
	NamedObject<int> kvp1("robert", 1);  //call const char* version, because "robert" is a C-style string, best match const char* ctor
	NamedObject<int> kvp2("max", 2);
	NamedObject<int> kvp3(kvp1);
}

void test_copy_ctor() {

	std::string r("robert");
	std::string m("max");

	NamedObject<int> kvp1(r, 1);  //call const char* version, because "robert" is a C-style string, best match const char* ctor
	NamedObject<int> kvp2(m, 2);

	NamedObject<int> kvp3(kvp1);

	kvp1 = kvp2;  //ok


}

void test_HomeForSale_copy_ctor() {
	HomeForSale hfs1;
	HomeForSale hfs2;

	//HomeForSale hfs3(hfs1);   //copy ctor is deleted
	//hfs2 = hfs1;  //copy assign operator is deleted
}

int main()
{
	//test_copy_ctor();

	std::cin.get();

    return 0;
}

