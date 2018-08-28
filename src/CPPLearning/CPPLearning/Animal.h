#pragma once
#include <iostream>

class Animal
{
public:
	void print() const { std::cout << "animal" << std::endl; }
};

class Dog : public Animal
{
public:
	void print() const  { std::cout << "dog" << std::endl; }
};


