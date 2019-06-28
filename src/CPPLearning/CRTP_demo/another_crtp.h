#pragma once

#include <new>
#include <iostream>

//see effective c++ item 49:
/*

std::new_handler is used to when new a object but not enough memory,
the function pointer will be called

*/


//resource wrapper
class NewHandlerHolder {
public:
	explicit NewHandlerHolder(std::new_handler h) : m_h(h) {}
	~NewHandlerHolder() { std::set_new_handler(m_h); }

	NewHandlerHolder(const NewHandlerHolder&) = delete;
	NewHandlerHolder& operator=(const NewHandlerHolder&) = delete;

private:
	std::new_handler m_h;
};


//template class to create 
template<typename T>
class NewHandlerSupport {
public:
	static std::new_handler& set_new_handler(std::new_handler h) {
		std::new_handler oldhandler = currentHandler;
		currentHandler = h;
		return oldhandler;
	}

	static void* operator new(std::size_t size) /*throw(std::bad_alloc)*/ {
		NewHandlerHolder hoder(currentHandler);
		return ::operator new(size);
	}

private:
	static std::new_handler currentHandler;  //declaration
};

template<typename T> std::new_handler NewHandlerSupport<T>::currentHandler = nullptr;  //definiton, initilize to nullptr

//using CRTP
//now t_foo have inherite base class method
class t_foo : public NewHandlerSupport<t_foo> {

};


//custom new_handler implementation
void outOfMemoty() {
	std::cerr << "out of memory" << std::endl;
	std::abort();
}

void test_new_handler() {

	t_foo::set_new_handler(outOfMemoty);  //set custom new_handler
	t_foo* f1 = new t_foo();  //if not enough memory, will call outOfMemory

	int* arr = new int[100000];  //if not enough memory , will call global default new_handler

	delete f1;
	delete arr;
}