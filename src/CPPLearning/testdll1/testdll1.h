#pragma once

#ifdef DLL1_EXPORT

#define DLL1_API __declspec(dllexport)

#else

#define DLL1_API __declspec(dllimport)

#endif // DLL1_EXPORT

DLL1_API void foo();