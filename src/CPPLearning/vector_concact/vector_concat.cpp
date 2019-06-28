#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>


class foo {
public:
	foo() : data(new char[1024]) {
		std::cout << "foo ctor" << std::endl;
	}

	~foo() {
		std::cout << "foo dtor" << std::endl;
		delete[] data;
	}

	foo(const foo& rhs) {
		std::cout << "foo copy ctor" << std::endl;

		data = new char[1024];
		memcpy_s(data, 1024, rhs.data, 1024);
	}

	foo& operator=(const foo& rhs) {
		std::cout << "foo copy assign operator" << std::endl;
		if (this == &rhs) return *this;

		char* temp = new char[1024];
		delete[] data;
		data = temp;
		memcpy_s(data, 1024, rhs.data, 1024);
		temp = nullptr;
		return *this;
	}

	foo(foo&& rhs) {
		data = rhs.data;
		rhs.data = nullptr;
	}

	foo& operator=(foo&& rhs) {

		//todo: use swap function to get exception-safe
		if (this == &rhs) return *this;

		delete[] data;

		data = rhs.data;
		rhs.data = nullptr;
		return *this;
	}

private:
	char* data;
};

void test_simple() {
	std::vector<int> v1{ 1,2,3,4,5 };
	std::vector<int> v2{ 6,7,8,9,10 };

	v1.insert(v1.end(), std::make_move_iterator(v2.begin()), std::make_move_iterator(v2.end()));

	for (auto& ent : v1) {
		std::cout << ent << " ";
	}

	std::string str("robert");
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	std::cout << std::endl;
}

void test_foo_by_value() {
	//vector foo value
	/*
	reserve 和一开始就初始化的区别

	std::vector<foo> v1(3);  //会直接初始化3个实例在vector里面，调用三次默认的ctor,  v1.size = 3

	std::vector<foo> v1;
	v1.reserver(3); //不会初始化，只有先申请3个对象的内存， v1.size == 0
	*/


	std::vector<foo> v1;
	v1.reserve(3);

	v1.emplace_back(foo());  //check if move ctor is called?
	v1.emplace_back(foo());
	v1.emplace_back(foo());

	std::vector<foo> v2;

	v2.emplace_back(foo());

	v2.reserve(v1.size() + v2.size());

	//check foo copy ctor is called?
	v2.insert(v2.end(), v1.begin(), v1.end());

	//check whether move ctor is called?  no move ctor, call copy ctor
	v2.insert(v2.end(), std::make_move_iterator(v1.begin()), std::make_move_iterator(v1.end()));

	//vector foo pointer

	//if vector contain pointer??
	v1.clear();
	v2.clear();


}

void test_foo_by_pointer() {

	/*
	vector里面存的是指针的话，这个不涉及到对象的移动，因为vector里面存的是指针的地址（类似于int）
	这时候移动一个int值和拷贝是一样的。
	*/

	std::vector<foo*> v1;
	std::vector<foo*> v2;

	v1.reserve(3);
	v2.reserve(1);

	v1.emplace_back();  //can compile:push back a NULL
	v1.emplace_back(new foo());
	v1.emplace_back(new foo());

	v2.emplace_back(new foo());

	v2.insert(v2.end(), v1.begin(), v1.end());

	v2.insert(v2.end(), std::make_move_iterator(v1.begin()), std::make_move_iterator(v1.end()));
}

void test_foo_by_ref() {
	
}

void test_vector() {
	std::vector<foo> v1(3);
	foo f;
	for (int i = 0; i < v1.size(); ++i) {
		v1[i] = f;  //check if call assign operator？ yes!!!
	}

	std::vector<foo> v2;
	v2.reserve(3);

	v2.emplace_back(f);
}

int main() {
	//test_foo_by_value();
	//test_foo_by_pointer();
	test_vector();
}
