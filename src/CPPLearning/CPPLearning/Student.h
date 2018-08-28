#pragma once
#include <string>
#include <iostream>
class Student
{
	friend void print_name(Student &std);
public:
	Student(std::string str) : name(str) {}

private:
	std::string name;
};

void print_name(Student &stu)
{
	std::cout << stu.name << std::endl;
}



