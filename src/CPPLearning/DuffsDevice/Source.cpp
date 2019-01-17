#include <stdio.h>


/*
duff's device

主要的思想是:

不适用stack来保存caller和人callee的参数和返回值，使用一个static变量
来保存上一次调用的返回位置，然后通过switch-case

用来减少分支的判断带来的开销
如下面的代码，normal_copy的情况下在for loop中需要循环size个比较
但是在duff优化后的代码中，只需要比较size/8次
这样减少了7/8 *size 的比较带来的开销


loop unrolling

8不是固定的，可以增加该值

缺点：

代码冗余，不太容易维护

*/


void normal_copy(char* to, const char* from, size_t size) {
	for (int i = 0; i < size; ++i) {
		*to++ = *from++;
	}
}

void duff_copy(char* to, const char* from, size_t size) {
	switch ((size%8))
	{
	case 0: do {
		*to++ = *from++;
	case 7: *to++ = *from++;
	case 6: *to++ = *from++;
	case 5: *to++ = *from++;
	case 4: *to++ = *from++;
	case 3: *to++ = *from++;
	case 2: *to++ = *from++;
	case 1: *to++ = *from++;
	} while (size / 8 > 0);
	}
}

void test_duff_device() {
	const char source[] = "hello";
	char dest[sizeof(source)];

	duff_copy(dest, source, sizeof(source));
}


int range(int a, int b)
{
	static long long int i;
	static int state = 0;
	switch (state)
	{
	case 0: /* start of function */
		state = 1;
		for (i = a; i < b; i++)
		{
			return i;

			/* Returns control */
	case 1:; /* resume control straight
				after the return */
		}
	}
	state = 0;
	return 0;
}

void test_range() {
	int i;
	for (;i = range(1, 5);) {  //return i=0 then for loop check return false
		printf("control at main: %d\n", i);
	}

}


int main(int argc, char* args[]) {
	test_range();
	getchar();

	return 0;
}