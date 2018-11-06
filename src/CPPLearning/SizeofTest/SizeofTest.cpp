// SizeofTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

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
class A {
	int a;//4
	float f;//4
	char c1;//1
	char c2;//1
	char d[4];//6, padding 2?
};

//sizeof: 16
class B {
	int a;//4
	float f;//4
	char c1;//1, padding 1
	char c2;//1, padding 1
	char d[5];  //6, padding 1
};


//sizeof: 8
struct TC1
{
	float x; //4
	char n[1];  //add padding 3
};

//sizeof: 6
struct TC2 {
	short s;  //2
	char n[3]; //4
};


//sizeof: 12
struct TC3
{
	char Data1;  //add padding 1
	short Data2;
	int Data3;
	char Data4;  //add padding 3
};

//reorder data member change the size of class
//sizeof: 8
struct TC4 
{
	char Data1;
	char Data4;
	short Data2;
	int Data3;
};

int main()
{
	size_t size = sizeof(Point_t);  //8
	size = sizeof(Point);  //8
	size = sizeof(A);
	size = sizeof(B);
	size = sizeof(TC1);
	size = sizeof(TC2);
	size = sizeof(TC3);
	size = sizeof(TC4);

}
