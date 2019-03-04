#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <algorithm>

int main() {

	std::vector<char> v(99);

	char buf[100 * 3];

	//auto it = cbegin()
	if (v.size() < 100) {
		int written = 0;
		auto it = v.cbegin();
		while (it != v.cend())
		{
			written += sprintf_s(buf + written, 100 * 3 - written, "%02x ", *it);
			++it;
		}

		buf[written] = '\0';
		printf("%s\n", buf);
	}


	return 0;

}