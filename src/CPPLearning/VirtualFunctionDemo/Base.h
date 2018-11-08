//#pragma once

#include <iostream>
#include <cassert>

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



struct Base1 {}; // empty class

struct Derived1 : Base1 {
	int i;
};

struct Derived2 : Base1 {
	Base1 c; // Base, occupies 1 byte, followed by padding for i
	int i;
};

struct Derived3 : Base1 {
	Derived1 c; // derived from Base, occupies sizeof(int) bytes
	int i;
};

void test_sizeof_class() {
	size_t temp;
	temp = sizeof(Derived1);  //4
	temp = sizeof(Derived2);  //8
	temp = sizeof(Derived3);  //8

	// empty base optimization does not apply,
	// base occupies 1 byte, Base member occupies 1 byte
	// followed by 2 bytes of padding to satisfy int alignment requirements
	assert(sizeof(Derived2) == 2 * sizeof(int));

	// empty base optimization does not apply,
	// base takes up at least 1 byte plus the padding
	// to satisfy alignment requirement of the first member (whose
	// alignment is the same as int)
	assert(sizeof(Derived3) == 3 * sizeof(int));
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