#pragma once

#ifdef  DLL1_EXPORTS

#define MATH_API __declspec(dllexport)
#else 
#define MATH_API __declspec(dllimport)
#endif //  DLL1_EXPORTS


namespace dllmathfuncs {
	class my_math_func {
	public:
		static MATH_API int add(int a, int b);
	};

	MATH_API int sub(int a, int b);
}

extern "C" {

	MATH_API int __stdcall foo(int a, int b);
	MATH_API void __cdecl bar(int a);
}


