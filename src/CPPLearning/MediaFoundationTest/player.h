#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <Shlwapi.h>

//media foundation header
#include <mfapi.h>
#include <evr.h>




template<typename T>
void SafeRelease(T **ppt) {
	if (*ppt) {
		(*ppt)->Release();
		*ppt = NULL;
	}
}



class Player : public IMFAsyncCallback {
public:

	//IUnkonwn method
	HRESULT WINAPI QueryInterface(REFIID iid, void** ppv) {
		static const QITAB qit[] =
		{
			QITABENT(CPlayer, IMFAsyncCallback),
			{ 0 }
		};
		return QISearch(this, qit, iid, ppv);
	}
	ULONG WINAPI AddRef() {

	}
	ULONG WINAPI Release() {

	}


	//IMFAsyncCallback method
	HRESULT WINAPI GetParameters(DWORD *flags, DWORD* queue) {
		return E_NOTIMPL;
	}

	HRESULT WINAPI Invoke(IMFAsyncResult* pAsyncResult) {
		//todo: session event 



		return S_OK;
	}

private:

	ULONG m_refcnt;
	IMFMediaSession* pSession;
};