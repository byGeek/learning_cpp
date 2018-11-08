#include "stdafx.h"
#include "math.h"

namespace libmathfuncs {
	int my_math_func::add(int a, int b) {
		return a + b;
	}

	
}

int __stdcall sub(int a, int b) {
	return a - b;
}

int __cdecl mul(int a, int b) {
	return a * b;
}