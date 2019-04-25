#include <stdio.h>
#include <stdlib.h>
#include <string>

int main() {
	char buf1[256] = { 0 };
	char buf2[128] = { 0 };

	char* ch = NULL;
	*ch = 'p';

	memcpy_s(buf2, 128, buf2, 256);
}