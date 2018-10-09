#pragma once

#include <iostream>
#include <string>

template<typename T>
class NamedObject
{
public:
	//NamedObject(const char*, const T&);
	NamedObject(const std::string&, const T&);

private:
	T value;
	std::string name;

	/*
	if name is a reference, i.e.
	std::string& name;

	then the compiler will not generate copy assignment operator, because reference can not be assign twice
	the compiler will declare the copy assignment operator function as deleted!
	*/
};

//template<typename T> NamedObject<T>::NamedObject(const char* key, const T& value) :
//	value(value), name(key) {
//	std::cout << "called in const char* ctor" << std::endl;
//}

template<typename T> NamedObject<T>::NamedObject(const std::string& key, const T& value) :
	value(value), name(key)
{
	std::cout << "called in string ctor" << std::endl;
}