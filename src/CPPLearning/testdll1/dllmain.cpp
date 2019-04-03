#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModuel,
	DWORD reason_for_call,
	LPVOID lpReserved) {


	switch (reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugStringW(L"process attach\n");
		break;
	case DLL_THREAD_ATTACH:
		OutputDebugStringW(L"thread attach\n");
		break;
	case DLL_PROCESS_DETACH:
		OutputDebugStringW(L"process detach\n");
		break;
	case DLL_THREAD_DETACH:
		OutputDebugStringW(L"thread detach\n");
		break;
	default:
		break;
	}

	/*
	if return false, then the application linked with this dll will fail
	*/
	return true;
}