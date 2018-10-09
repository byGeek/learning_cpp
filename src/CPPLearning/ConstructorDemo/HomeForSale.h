#pragma once

class HomeForSale
{
public:
	HomeForSale() = default;  //default ctor
	~HomeForSale() = default;  //default dtor

	HomeForSale(const HomeForSale& rhs) = delete;  //copy ctor
	HomeForSale& operator=(const HomeForSale& rhs) = delete;  //copy assign operator
};
