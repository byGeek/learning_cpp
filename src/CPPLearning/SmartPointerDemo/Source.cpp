
#include <iostream>
#include "test_unique_ptr.h"

void test_unique_ptr() {
	auto ptr = makeInvestment();
	//check ptr dtor

	//in std::unique_ptr
	//if base class dtor is not virtual, then compiler will
	//ONLY call base class dtor
}

void test_shared_ptr() {
	auto ptr = doInvestment();

	//in std::shared_ptr
	//if base class dtor is not virtual, compiler will
	//call derived class dtor corectlly!!!
}

int main() {
	//test_unique_ptr();
	test_shared_ptr();
	

}