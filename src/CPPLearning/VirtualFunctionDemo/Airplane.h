#pragma once

#include <iostream>
#include <string>

class Airplane
{
public:
	virtual void fly() = 0;
};


//base class can give a pure virtual function a definiton
void Airplane::fly()
{
	std::cout << "default fly from airplane" << std::endl;
}

class ModelA : public Airplane
{
public:
	void fly()  {
		Airplane::fly();
	}
};

class ModelB : public Airplane
{
public:

};
