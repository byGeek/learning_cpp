
#include "wavheader.h"
#include <string>
#include <iostream>

int main() {
	const std::wstring filename(L"D:\\support_32bit\\I2S1_vector.wav");
	const std::wstring record_filename(L"D:\\support_32bit\\record1_48000.wav");

	wav_header wavheader;
	BOOL ret;
	int offset = offsetof(wav_header, AudioFormat);

	ret = read_wav_header(&wavheader, record_filename.c_str());
	if (!ret) {
		std::cout << "read wav file header fail" << std::endl;
	}

}