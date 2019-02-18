#include <iostream>
#include <cstdio>


class my_buf {

public:
	my_buf() : buf(NULL), size(0) {

	}

	~my_buf() {
		if (buf != NULL) {
			free(buf);  //error, can not free stack memory, BAD DESIGN!!!
		}
	}


	char* buf;
	size_t size;

};

void test_buf(char* buf, size_t size) {
	my_buf mybuf;

	mybuf.buf = buf;
	mybuf.size = size;
}

int main() {

	char buf[1024];
	test_buf(buf, 1024);


	getchar();
	return 0;
}