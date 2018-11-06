#pragma once

#ifdef MY_EXPORTS
#define MY_API __declspec(dllexport)
#else
#define MY_API __declspec(dllimport)
#endif // MY_EXPORTS


