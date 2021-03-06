// SizeofTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

/*
The sizeof value for any structure is the offset of the final member, 
plus that member's size, rounded up to the nearest multiple of the 
largest member alignment value or the whole structure alignment value, 
whichever is larger.

*/


/*

ref: https://en.wikipedia.org/wiki/Data_structure_alignment
Padding is only inserted when a structure member is followed by a member
with a larger alignment requirement or at the end of the structure.
*/

typedef struct _point {
	float x;
	float y;
}Point_t;

//function
void print_point(const Point_t* ptr) {
	printf("%f %f", ptr->x, ptr->y);
}

class Point {
public:
	Point(float x, float y) : m_x(x), m_y(y) {}
	~Point() = default;

	void print() {
		printf("%f %f", m_x, m_y);
	}
	float x() { return m_x; }
	float y() { return m_y; }

private:
	float m_x;
	float m_y;
};

//sizeof: 16
//offset: 0 4 8 9 10
struct A {
	int a;//4
	float f;//4
	char c1;//1
	char c2;//1
	char d[4];//4 + 2 padding
};

//sizeof: 16
//offset: 0 4 8 9 10
struct B {
	int a;//4
	float f;//4
	char c1;//1
	char c2;//1
	char d[5];//5 + 1 padding
};


//sizeof: 8
//offset: 0 4 6
struct TC1
{
	float x; //4
	char n[1];//1 + padding 1
	short d;//2
};

void test_tc1() {
	/*
	The %zu format specifier was introduced specifically for size_t, 
	so as to clear the confusion of having to choose in between the 
	unsigned integer specifiers %u, %lu, and more recently %llu.
	*/
		

	printf("%zu ", offsetof(TC1, x));  //zu format specifier is for size_t type
	printf("%zu ", offsetof(TC1, n));
	printf("%zu\n", offsetof(TC1, d));
}

//sizeof: 6
//offset: 0 2
struct TC2 {
	short s;  //2
	char n[3]; //3+ 1 padding
};

void test_tc2() {
	printf("%zu ", offsetof(TC2, s));
	printf("%zu\n", offsetof(TC2, n));
}


//sizeof: 12
//offset : 0 2 4 8
struct TC3
{
	char Data1;  //1 + 1 padding
	short Data2;//2
	int Data3;//4
	char Data4;  //1 + 3 padding
};

void test_tc3() {
	printf("%zu %zu %zu %zu\n", offsetof(TC3, Data1), offsetof(TC3, Data2), offsetof(TC3, Data3), offsetof(TC3, Data4));
}

//reorder data member change the size of class
//sizeof: 8

//offset: 0 1 2 4
struct TC4 
{
	char Data1;//1
	char Data4;//1
	short Data2;//2
	int Data3;//4
};

void test_tc4() {
	printf("%zu %zu %zu %zu\n", offsetof(TC4, Data1), offsetof(TC4, Data4), offsetof(TC4, Data2), offsetof(TC4, Data3));
}

//siseof: 6
//offset: 0 2 4
struct TC5 {
	short d1;
	short d2;
	short d3;
};

void test_tc5() {
	printf("sizeof TC5: %zu, offset: ", sizeof(TC5));
	printf("%zu %zu %zu\n", offsetof(TC5, d1), offsetof(TC5, d2), offsetof(TC5, d3));
}

void test_sizeof_class() {
	size_t size = sizeof(Point_t);  //8
	size = sizeof(Point);  //8
	size = sizeof(A);
	size = sizeof(B);
	size = sizeof(TC1);
	size = sizeof(TC2);
	size = sizeof(TC3);
	size = sizeof(TC4);
}

void test_memeber_offset() {
	//data member offset in struct A

	printf("%zu ", offsetof(A, a));
	printf("%zu ", offsetof(A, f));
	printf("%zu ", offsetof(A, c1));
	printf("%zu ", offsetof(A, c2));
	printf("%zu\n ", offsetof(A, d));
	

	printf("%zu ", offsetof(B, a));
	printf("%zu ", offsetof(B, f));
	printf("%zu ", offsetof(B, c1));
	printf("%zu ", offsetof(B, c2));
	printf("%zu\n ", offsetof(B, d));
}

int main()
{
	//test_memeber_offset();
	test_tc1();
	test_tc2();
	test_tc3();
	test_tc4();
	test_tc5();

	getchar();

}
