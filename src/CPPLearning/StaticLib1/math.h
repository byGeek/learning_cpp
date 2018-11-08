#pragma once

namespace libmathfuncs
{
	class my_math_func {
	public:
		static int add(int a, int b);
	};

	
}

extern "C" {
	int __stdcall sub(int a, int b);
	int __cdecl mul(int a, int b);
}
