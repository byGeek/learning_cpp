#include <Windows.h>
#include <stdio.h>
#include <cassert>


#include "wavfile.h"

enum {
	E_OK,
	E_FILE_TOO_LARGE,
	E_INVALID_HANDLE,
	E_MMF_FAIL
};


void create_wav_header(wav_header* pheader, unsigned int num_of_channels,
	unsigned int sample_rate, unsigned int sample_depth,
	unsigned int data_size) {

	assert(pheader != NULL);
	fill_default_wav_header(pheader);

	pheader->ChunkSize = data_size + 44 - 8;
	pheader->Subchunk1Size = 16;  //16 for PCM
	pheader->AudioFormat = 1;  //PCM
	pheader->NumOfChan = num_of_channels;
	pheader->SamplesPerSec = sample_rate;
	pheader->bytesPerSec = sample_rate * num_of_channels * sample_depth / 8;
	pheader->blockAlign = num_of_channels * sample_depth / 8;
	pheader->bitsPerSample = sample_depth;
	pheader->Subchunk2Size = data_size;
}

int fill_wav_header(wav_header* pheader, const wchar_t* const filename) {

	fill_default_wav_header(pheader);

	HANDLE hfile = CreateFile(filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL
	);

	if (hfile == INVALID_HANDLE_VALUE) {
		return E_INVALID_HANDLE;
	}

	DWORD size_high = 0;
	DWORD size_low = 0;


	//wav file is limited to less then 4G
	//so size_high must be 0
	size_low = GetFileSize(hfile, &size_high);
	CloseHandle(hfile);

	if (size_high != 0) {
		return E_FILE_TOO_LARGE;
	}

	//todo: 2 channels, 16 bit, 16KHz

	pheader->ChunkSize = size_low + 44 - 8;
	pheader->Subchunk1Size = 16;
	pheader->AudioFormat = 1;
	pheader->NumOfChan = 2;
	pheader->SamplesPerSec = 16000; //16KHz
	pheader->bytesPerSec = 16000 * 2 * 16 / 8;
	pheader->blockAlign = 2 * 16 / 8;
	pheader->bitsPerSample = 16;
	pheader->Subchunk2Size = size_low;
}

DWORD get_system_granularity() {
	static SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwAllocationGranularity;
}

//in unicode envirronment, use char ?
BOOL convert_pcm2wav(const wchar_t* const filename, wav_header* pHeader) {

	assert(filename != NULL);
	assert(pHeader != NULL);

	HANDLE hpcm = INVALID_HANDLE_VALUE;
	HANDLE hwav = INVALID_HANDLE_VALUE;

	HANDLE hPcmMappingObj = NULL;
	//HANDLE hWavMappingObj = NULL;
	//HANDLE hMappingViewObj = NULL;

	DWORD pcm_filesize_low = 0;
	DWORD pcm_filesize_high = 0;

	//TODO: use mmf file to load wav file
	__try {
		hpcm = CreateFileW(filename,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		if (hpcm == INVALID_HANDLE_VALUE) {
			return E_INVALID_HANDLE;
		}

		pcm_filesize_low = GetFileSize(hpcm, &pcm_filesize_high);
		if (pcm_filesize_high != 0) {
			return E_FILE_TOO_LARGE;
		}

		hPcmMappingObj = CreateFileMappingW(hpcm,
			NULL,
			PAGE_READONLY,
			0,
			0,
			NULL);
		if (hPcmMappingObj == NULL) {
			return E_MMF_FAIL;
		}

		hwav = CreateFileW(L"output_wav.wav",
			GENERIC_READ | GENERIC_WRITE,
			0,  //exclusive access
			NULL,
			CREATE_NEW,
			0,
			NULL
		);
		if (hwav == INVALID_HANDLE_VALUE) {
			return E_INVALID_HANDLE;
		}

		//set wav file size
		SetFilePointer(hwav, pcm_filesize_low + sizeof(wav_header), 0, FILE_BEGIN);
		SetEndOfFile(hwav);

		/*hWavMappingObj = CreateFileMapping(hwav,
			NULL,
			PAGE_READWRITE,
			0,
			0,
			NULL);
		if (hWavMappingObj == NULL) {
			return E_MMF_FAIL;
		}*/

		DWORD allocation_granularity = get_system_granularity();
		DWORD size_processed = 0;
		DWORD size_per_loop = 0;
		DWORD written_per_loop = 0;

		//reset file offset pointer to start position
		SetFilePointer(hwav, 0, 0, FILE_BEGIN);
		WriteFile(hwav, pHeader, sizeof(wav_header), &written_per_loop, NULL); //write header
		assert(written_per_loop == sizeof(wav_header));

		while (size_processed < pcm_filesize_low) {
			if (pcm_filesize_low - size_processed > allocation_granularity) {
				size_per_loop = allocation_granularity;
			}
			else {
				size_per_loop = pcm_filesize_low - size_processed;  //last loop
			}
			/*
			The combination of the high and low offsets must specify an offset within 
			the file mapping. They must also match the memory allocation granularity 
			of the system. That is, the offset must be a multiple of the allocation 
			granularity. To obtain the memory allocation granularity of the system, 
			use the GetSystemInfo function, which fills in the members of a SYSTEM_INFO
			structure. 
			*/
			BYTE* pPcmData = (BYTE*)MapViewOfFile(hPcmMappingObj,
				FILE_MAP_READ,
				0, //high DWORD
				size_processed,  //low DWORD
				size_per_loop
			);
			if (pPcmData == NULL) {
				return E_MMF_FAIL;
			}

			//todo: memcpy
			//use MMF to write wav file?
			/*BYTE* pWavData = (BYTE*)MapViewOfFile(hWavMappingObj,
				FILE_MAP_WRITE | FILE_MAP_READ,
				0,
				)*/
			WriteFile(hwav, pPcmData, size_per_loop, &written_per_loop, NULL);
			assert(size_per_loop == written_per_loop);
			size_processed += size_per_loop;
		}
	}
	__finally {
		//todo: close mapping object
		if (hPcmMappingObj != NULL) {
			CloseHandle(hPcmMappingObj);
		}
		if (hpcm != INVALID_HANDLE_VALUE) {
			CloseHandle(hpcm);
		}
		if (hwav != INVALID_HANDLE_VALUE) {
			CloseHandle(hwav);
		}
	}
	return TRUE;
}

int wmain() {

	wav_header wavheader;
	const wchar_t* const pcm = L"vector_16000.pcm";
	const wchar_t* const wav = L"vector_16000.wav";

	read_wav_header(&wavheader, wav);
	convert_pcm2wav(pcm, &wavheader);

	return 0;
}