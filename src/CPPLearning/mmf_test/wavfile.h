#ifndef _WAV_FILE_H

#define _WAV_FILE_H

#include <cstdint>
#include <stdio.h>

/*
you should not use unsinged long, short or even char or other such types 
for reading binary files. The size and signedness of those types may not
be exactly what you expect them to be (especially long which can be either
32 or 64 bits depending on platform). Instead use the types from <cstdint>
, like uint32_t etc


typedef struct {
	char RIFF[4];
	unsigned long chunkSize;
	char WAVE[4];
	char FMT[4];
	unsigned long subChunk1Size;
	unsigned short audioFormat;
	unsigned short numOfChannels;
	unsigned long sampleRate;
	unsigned long byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char DATA[4];
	unsigned long subChunk2Size;

} WavHeader, *PWavHeader;

*/

typedef struct
{
	/* RIFF Chunk Descriptor */
	uint8_t         RIFF[4];        // RIFF Header Magic header
	uint32_t        ChunkSize;      // RIFF Chunk Size
	uint8_t         WAVE[4];        // WAVE Header
	/* "fmt" sub-chunk */
	uint8_t         fmt[4];         // FMT header
	uint32_t        Subchunk1Size;  // Size of the fmt chunk
	uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
	uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
	uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
	uint32_t        bytesPerSec;    // bytes per second
	uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
	uint16_t        bitsPerSample;  // Number of bits per sample
	/* "data" sub-chunk */
	uint8_t         data[4]; // "data"  string
	uint32_t        Subchunk2Size;  // Sampled data length
} wav_header;


void fill_default_wav_header(wav_header* pwav_header) {

	if (pwav_header != NULL) {

		memset(pwav_header, 0, sizeof(wav_header));

		const uint8_t riff[] = { 'R', 'I', 'F', 'F' };
		const uint8_t fmt[] = { 'f', 'm', 't', ' ' };
		const uint8_t data[] = { 'd', 'a', 't', 'a' };
		const uint8_t wave[] = { 'W', 'A', 'V', 'E' };

		memcpy_s(&pwav_header->RIFF, 4, riff, 4);
		memcpy_s(&pwav_header->fmt, 4, fmt, 4);
		memcpy_s(&pwav_header->data, 4, data, 4);
		memcpy_s(&pwav_header->WAVE, 4, wave, 4);
	}
}

BOOL read_wav_header(wav_header* pheader, const wchar_t* const filename) {
	assert(pheader != NULL);
	assert(filename != NULL);

	HANDLE hfile = CreateFileW(filename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);
	if (hfile == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	DWORD byteRead = 0;
	ReadFile(hfile, (PVOID)pheader, sizeof(wav_header), &byteRead, NULL);
	assert(sizeof(wav_header) == byteRead);

	if (strncmp((const char*)pheader->RIFF, "RIFF", 4) != 0) {
		CloseHandle(hfile);
		return FALSE;
	}
	if (strncmp((const char*)pheader->fmt, "fmt ", 4) != 0) {
		CloseHandle(hfile);
		return FALSE;
	}
	if (strncmp((const char*)pheader->data, "data", 4) != 0) {
		CloseHandle(hfile);
		return FALSE;
	}
	if (strncmp((const char*)pheader->WAVE, "WAVE", 4) != 0) {
		CloseHandle(hfile);
		return FALSE;
	}

	SetFilePointer(hfile, pheader->ChunkSize + 8 -1, 0, FILE_BEGIN);
	BYTE buf[1];
	BOOL r = ReadFile(hfile, buf, 1, &byteRead, NULL);
	if (!r) {
		CloseHandle(hfile);
		return false;
	}

	CloseHandle(hfile);
	return TRUE;
}

#endif // !_WAV_FILE_H

