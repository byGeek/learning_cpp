#include <Windows.h>
#include <assert.h>
#include <stdio.h>

//media foundation header
#include <mfapi.h>
#include <evr.h>

#pragma comment(lib, "shlwapi")

static const wchar_t WAV_FILE[] = L"test.wav";



int wmain() {

	IMFMediaSession* pSession = NULL;
	IMFTopology* pTopology = NULL;



	HRESULT hr = MFStartup(MF_VERSION);
	if (FAILED(hr)) {
		goto done;
	}


	hr = MFCreateMediaSession(NULL, &pSession);
	if (FAILED(hr)) {
		goto done;
	}

	pSession->BeginGetEvent()

done:
	MFShutdown();
	return 0;
}