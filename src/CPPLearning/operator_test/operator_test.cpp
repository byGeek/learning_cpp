#include <iostream>


class foo {
public:
	foo(int x, int y) : m_x(x), m_y(y){}
	~foo() = default;

	foo(const foo& other) {
		m_x = other.m_x;
		m_y = other.m_y;
	}
	foo& operator=(const foo& other) {
		if (this == &other) {
			return *this;
		}

		m_x = other.m_x;
		m_y = other.m_y;

		return *this;
	}

	foo& operator+(const foo& other) {
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}

	int get_x() const{
		return m_x;
	}

	int get_y() const {
		return m_y;
	}


private:

	int m_x;
	int m_y;
};

int main() {
	foo f1(1, 2);
	foo f2(2, 3);

	foo f3(f1);
	foo f4 = f2;  //copy ctor
	f4 = f3;  //copy assign

	foo f5 = f1 + f2;  //call overloaded operator +, expand to   f1.operator+(f2)

	/*
	can not create user-defined operator, can not overload existing operator!
	*/

	std::cout << f5.get_x() << " " << f5.get_y() << std::endl;
}