#pragma once

#include <cassert>
#include <iostream>

template<typename T>
class Singleton {
public:
	static T& getInstance() {
		static T t;
		return t;
	}

	//inside template, Singleton can be stand for Singleton<T> 
	//that means:

	/*
	Singleton<T>();

	equals to:

	Singleton();
	
	*/

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

protected:  //usally ctor should be private to avoid expose publicly, but 
	//as a base class, its derived class should be able to call it
	Singleton() = default;

	/*
	see ref: https://codereview.stackexchange.com/questions/173929/modern-c-singleton-template
	Although the constructor is public, it can't be called without a Singleton<T>::token object, 
	meaning that access to it is now controlled.
	*/

	struct token{};  
};


//generic singleton using CRTP
//curiously returning template pattern

class cfoo : public Singleton<cfoo> {
public:
	/*
	cfoo() { std::cout << "cfoo ctor" << std::endl; }
	~cfoo() { std::cout << "cfoo dtor" << std::endl; }
	*/
	void test() {}
};

class cbar : public Singleton<cbar> {
public:
	/*
	cbar() { std::cout << "cbar ctor" << std::endl; }
	~cbar() { std::cout << "cbar dtor" << std::endl; }
	*/
	void bar_test(){}
};

class czoo :public Singleton<czoo> {
public:
	//czoo(token t) {}
};


void test_if_single() {
	cfoo& f1 = cfoo::getInstance();
	cfoo& f2 = cfoo::getInstance();

	//cfoo f3;

	//assert(&f1 == &f3);

	//cfoo f3;

	assert(&f1 == &f2);  //test if reference same object

	cbar& b1 = cbar::getInstance();
	cbar& b2 = cbar::getInstance();

	assert(&b1 == &b2);

}


//simple singleton implementation
class my_singleton {
public:
	my_singleton(const my_singleton&) = delete;
	my_singleton& operator=(const my_singleton&) = delete;

	static my_singleton& getInstance() {
		static my_singleton instance;  //call private ctor 
		return instance;
	}

private:
	my_singleton() = default;
};

void test_simple_singleton() {
	my_singleton& c1 = my_singleton::getInstance();
	my_singleton& c2 = my_singleton::getInstance();

	assert(&c1 == &c2);
}