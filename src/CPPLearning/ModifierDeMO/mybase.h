#pragma once

#include <iostream>

class mybase
{
public:
	void non_virtual_fun() { std::cout << "from mybase: non_virtual_fun" << std::endl; }
	virtual void virtual_func() { std::cout << "from mybase: virtual_func" << std::endl; }

	//NOTE!!!
	//never redefined a inherited virtual function default parameter value
	//BAD CODE
	virtual void virtual_func(int a, int defaultval = 1) { std::cout << "default value: " << defaultval << std::endl; }
};

class myderived : public mybase
{
public:
	void non_virtual_fun() { std::cout << "from derived: non_virtual_fun" << std::endl; }
	void virtual_func() override { std::cout << "from derived: virtual_func" << std::endl; }

	virtual void virtual_func(int a, int defaultval = 2) { std::cout << "default value: " << defaultval << std::endl; }
};
