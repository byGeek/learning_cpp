// VirtualFunctionDemo.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "stdafx.h"
#include "Airplane.h"

int main()
{
	Airplane* plane = new ModelA();
	plane->fly();

	std::cin.get();
    return 0;
}

