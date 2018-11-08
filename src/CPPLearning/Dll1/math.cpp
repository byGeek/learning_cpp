#include "stdafx.h"
#include "math.h"

namespace dllmathfuncs {
	int my_math_func::add(int a, int b) {
		return a + b;
	}

	int sub(int a, int b) {
		return a - b;
	}
}


int __stdcall foo(int a, int b) {
	return 0;
}

void __cdecl bar(int a) {

}