#pragma once

class X {};

class Y : public virtual X {};  //virtual inheritance
class Z : public virtual X {};  //virtual inheritance

class A :public Y, public Z {};


class Q : public X {
//public:
//	virtual void foo() {};  //virtual method here
//private:
//	int data;
};

class P : public X {
private:
	int data;
};

void test_sizeof_XYZ() {
	size_t temp = sizeof(X); //1

	X *x = new X();
	Z *z = new Z();
	Y *y = new Y();
	Q *q = new Q();
	A *a = new A();
	temp = sizeof(Y);  //4
	temp = sizeof(Z);  //4
	temp = sizeof(A);  //8
	temp = sizeof(Q);  //1
	temp = sizeof(P);  //4

}
