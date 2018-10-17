#include "pch.h"

class Base
{
public:
	void pub_mem(){}

protected:
	void pro_mem() {}

private:
	void pri_mem() {}
};


//public inheritance
class Pub_Derived : public Base
{
public:
	void f() { pub_mem(); }

	void g() { pro_mem(); }

	/*void h() { pri_mem(); }*/  //can not access private member in base class
};

class Priv_Derived : private Base
{
public:
	void f() { pub_mem(); }
	void g() { pro_mem(); }  //can access protected memeber and public memeber
};


class Prot_Derived : private Base
{
public:
	void f() { pub_mem(); }
	void g() { pro_mem(); }
};

//instance test
void test()
{
	Pub_Derived d1;
	d1.pub_mem();
	/*d1.pro_mem();*/  //can not access

	Prot_Derived d2;
	//d2.pub_mem(); //because Prot_Derived will inherite base member as its PROTECTED member, so can not access protected memeber 
	//d2.pro_mem();

	Priv_Derived d3;
	//d3.pub_mem();  //same reason above
	//d3.pro_mem();
}