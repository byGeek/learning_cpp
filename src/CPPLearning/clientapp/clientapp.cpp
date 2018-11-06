// clientapp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "../StaticLib1/math.h"
#include "../Dll1/math.h"


int main()
{
	/*
	  use static library, need to reference static lib in project reference

	  1. no need to export symbols because we will actually compile the static lib to our application
	  2. so we need to reference static lib in project reference setting

	*/
	auto ret = libmathfuncs::my_math_func::add(1, 2);


	/*
	need use import lib for dynamic link, set link->input->dll1.lib

	1. we need to export symbols in dll
	2. in our application link setting, we need to specify the import library(dll1.lib) to
	tell linker where to find symbols
	*/
	auto ret2 = dllmathfuncs::my_math_func::add(1, 2);  
	return 0;
}
