//#pragma once

#include <iostream>

class Base
{
public:
	virtual void foo(){}
	virtual void bar() { std::cout << "in base" << std::endl; }
	void real(){}
	int data_in_base;
};

class Derived : public Base
{
public:
	virtual void h() {};
	void bar(int) { std::cout << "in derived" << std::endl; }
	virtual void bar() { std::cout << "in derived" << std::endl; }
	int data_in_derived;
};

void test_vtable() {
	Base* b1 = new Base();
	Base* b2 = new Derived();
	b2->bar();

	Derived* d1 = new Derived();
	d1->bar(1);

	delete b1;
	delete b2;
}
