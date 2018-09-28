#pragma once

#ifdef TESTDLL_EXPORTS

#define TESTDLL_API __declspec(dllexport)
#else
#define TESTDLL_API __declspec(dllimport)

#endif // TESTDLL_EXPORTS

TESTDLL_API int add(int a, int b);