#include <iostream>

class singleton {
public:
	~singleton() {
		delete (char*)data;
	}

	static singleton& get_instance() {
		static singleton self;
		return self;
	}

	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;

	void do_something() {}

private:

	singleton() {
		data = new char[1024];
	}
	void* data;
};


template<typename T>
class Singleton {
public:
	~Singleton();

	static T& getInstance() {
		static T t;
		return t;
	}
private:
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator&(const Singleton&);

};

class foo : public Singleton<foo> {
public:
	/*can not declare public foo ctor because Base class ctor is private*/
	//foo() {}
};

template<typename T>
class BaseCounter {
public:
	BaseCounter() {
		++m_cnt;
	}

	~BaseCounter() {
		--m_cnt;
	}

	const static int getcount() { return m_cnt; }

protected:
	static int m_cnt;
};

template<typename T> 
int BaseCounter<T>::m_cnt = 0;

class bar : public BaseCounter<bar> {
public:
	bar() = default;
	~bar() = default;
};

class myclass : public BaseCounter<myclass> {
public:

private:
	int dummy;
};


int main() {

	bar b1, b2, b3;
	myclass m1, m2, m3;

	auto t1 = b1.getcount();
	t1 = b2.getcount();
	t1 = b3.getcount();

	auto t2 = m1.getcount();
	t2 = m2.getcount();
	t2 = m3.getcount();

}