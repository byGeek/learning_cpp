#pragma once

#include <iostream>

//use CRTP to store a reference counter for every class

template<typename T>
class RefCounter {
public:
	RefCounter() { ++m_cnt; }
	~RefCounter() { --m_cnt; }

	RefCounter(RefCounter&) = delete;
	RefCounter& operator=(const RefCounter&) = delete;

	static int getRefCnt() { return m_cnt; }

protected:
	static int m_cnt;
};

template<typename T> int RefCounter<T>::m_cnt = 0;


//use CRTP to generate a class-specific RefCounter to hold the ref counter
class r_foo :public RefCounter<r_foo> {
public:
	r_foo(){}
	~r_foo() {}

	//add other function here
};

static void test_ref_cnt() {
	r_foo rf1;

	std::cout << "count: " << r_foo::getRefCnt() << std::endl;
	r_foo rf2;
	std::cout << "count: " << r_foo::getRefCnt() << std::endl;

	r_foo* rf3 = new r_foo();
	std::cout << "count: " << r_foo::getRefCnt() << std::endl;

	delete rf3;
	std::cout << "count: " << r_foo::getRefCnt() << std::endl;

}

void test_ref() {
	std::cout << "count: " << r_foo::getRefCnt() << std::endl;

	test_ref_cnt();
	std::cout << "count: " << r_foo::getRefCnt() << std::endl;

}