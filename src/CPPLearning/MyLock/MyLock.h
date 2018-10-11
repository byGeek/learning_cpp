#pragma once


#include <mutex>


//Use MyLock to manage mutex resource
//since c++ 11, there is a std::lock_guard class to do that
class MyLock
{
private:
	std::mutex* my_mutex;

public:
	MyLock(std::mutex* _mutex) : my_mutex(_mutex)
	{
		my_mutex->lock();
	}

	~MyLock() { my_mutex->unlock(); }

	MyLock(const MyLock& _mylock) = delete;  //delte copy ctor
};