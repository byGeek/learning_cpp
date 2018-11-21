#pragma once

#include <iostream>

//effective c++ item 44: 从template剥离跟参数无关的模板参数
//比如下面的第二个参数 site_t
//否则在不同的size_t参数会实例化不同的类，造成代码膨胀
template<typename T, std::size_t n>
class Matrix {
public:
	void invert() {}
};

template<typename T>
class matrix_base {
protected:
	void invert(std::size_t size) {};
};

template<typename T, std::size_t n>
class improved_matrix : private matrix_base {
public:
	void invert() { this->invert(n); }  //调用base中的invert，这样底层的实现是一样的

private:
	using matrix_base<T>::invert;
};
