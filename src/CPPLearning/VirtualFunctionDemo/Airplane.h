#pragma once

#include <iostream>
#include <string>

class Airplane
{
public:
	virtual void fly() = 0;
	int data;
};


//base class can give a pure virtual function a definiton
void Airplane::fly()
{
	std::cout << "default fly from airplane" << std::endl;
}

class ModelA : public Airplane
{
public:
	int data_in_a;
	void fly()  {
		Airplane::fly();
	}

	void foo() {
		std::cout << "out" << std::endl;
	}
	virtual void bar() {
		std::cout << "cout" << std::endl;
	}
};

class ModelB : public Airplane
{
public:

};

class C : public ModelA
{
public:
	int data_in_c;
	void c_func() {}
	virtual void c_virtual_func() {}
};

void test_virtual_func() {
	Airplane* plane = new ModelA();
	plane->fly();

	ModelA* modela = new ModelA();
	modela->fly();

	C* c1 = new C();
	Airplane* c2 = new C();
	ModelA* c3 = new C();

	modela->bar();
	modela->foo();
}
