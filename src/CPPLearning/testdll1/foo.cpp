#include "testdll1.h"
#include <Windows.h>


void foo() {
	OutputDebugStringW(L"called foo in dll1\n");
}