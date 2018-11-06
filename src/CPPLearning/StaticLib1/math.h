#pragma once

namespace libmathfuncs
{
	class my_math_func {
	public:
		static int add(int a, int b);
	};

	extern "C" {
		int sub(int a, int b);
	}
}
