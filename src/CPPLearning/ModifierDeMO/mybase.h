#pragma once

#include <iostream>

class mybase
{
public:
	void non_virtual_fun() { std::cout << "from mybase: non_virtual_fun" << std::endl; }
	virtual void virtual_func() { std::cout << "from mybase: virtual_func" << std::endl; }
};

class myderived : public mybase
{
public:
	void non_virtual_fun() { std::cout << "from derived: non_virtual_fun" << std::endl; }
	void virtual_func() override { std::cout << "from derived: virtual_func" << std::endl; }
};
