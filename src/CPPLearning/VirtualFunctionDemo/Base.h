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

class X {};

class Y : public virtual X{};
class Z: public virtual X{};

class A:public Y, public Z{};

void test_sizeof_class() {
	size_t temp = sizeof(X); //1
	temp = sizeof(Y);  //4
	temp = sizeof(Z);  //4
	temp = sizeof(A);  //8
}


class Point3D {
public: 
	virtual ~Point3D() {};

protected:
//	static Point3D origin;
	float x, y, z;
};


class Vetex : public Point3D {
public:
	void foo() {
		//std::cout << "&Point3D::x yeild: " << &Point3D::x << std::endl;  //suppose to equal offset in memory layout model?
		std::cout << "Vetex's x yield: " << &x << std::endl;  //pointer to data member
	}
};

void test_offset() {
	Vetex vt;
	vt.foo();
}