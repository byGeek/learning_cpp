
#include <iostream>

//#define SHORT_TEST

#ifdef SHORT_TEST

static const int DEFAULT_TIME = 1;

#else
static const int DEFAULT_TIME = 2;

#endif // SHORT_TEST


int main() {
	std::cout << "DEFAULT_TIME is : " << DEFAULT_TIME << std::endl;
	std::cin.get();
}