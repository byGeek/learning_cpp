#pragma once

#include <iostream>

//template meta programming

template<unsigned n>
struct Fabonachi {
	enum{value = n* Fabonachi<n-1>::value};
};


//template specialazation
template<>
struct Fabonachi<0> {
	enum { value = 1 };
};

void test_fabonachi() {
	std::cout << Fabonachi<10>::value << std::endl;
	std::cout << Fabonachi<5>::value << std::endl;
}
