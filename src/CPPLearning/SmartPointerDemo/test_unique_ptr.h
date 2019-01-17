#pragma once
#include <iostream>
#include <memory>
#include <functional>

#define MY_PRINT std::cout<< __FUNCTION__ << std::endl;

class Investment {
public:
	Investment(const char* name) : m_name(new char[128]){
		strcpy_s(m_name, 128, name);
		MY_PRINT;
	}


	//in base class most case you should make dtor virtual!!!
	virtual ~Investment() {
		delete m_name;
		MY_PRINT;
	}

	void release() {
		//do something , release 
	}
	//~Investment() {
	//	delete m_name;
	//	MY_PRINT;
	//}

protected:
	char* m_name;
};

class Stock : public Investment {
public:
 	Stock(const char* name) : Investment(name){
		MY_PRINT;
	}

	~Stock() {
		MY_PRINT;
	}

};



//template<typename T>
//std::unique_ptr<Investment> makeInvestment(T t) {
//	//return std::make_unique<Stock>(2);
//	std::unique_ptr<Stock> stock(new Stock("hello"));
//	return stock;
//}

std::shared_ptr<Investment> doInvestment() {
	return std::make_shared<Stock>("hello");
}

std::unique_ptr<Investment> makeInvestment() {
	//in c++ 11
	//std::unique_ptr<Stock> stock(new Stock("hello"));
	//return stock;

	auto ptr = new Stock("hello");
	std::unique_ptr<Investment> pInvest(ptr);

	return std::unique_ptr<Stock>(new Stock("hello"));
}

std::unique_ptr<Investment> makeInvestment2() {
	//in c++ 14
	return std::make_unique<Stock>("hello");
}

template<typename T, typename ... Args>
std::unique_ptr<T> make_unique(Args&&... params) {
	return std::unique_ptr<T>(new T(std::forward<Args>(params)...));
}

/*
specify custom deletor
*/


auto delInvest = [](Investment* pInvestment) {
	//do something
	delete pInvestment;
};



std::unique_ptr<Investment, decltype(delInvest)> ptr(new Stock("hello"), delInvest);

void delInv(Investment* pInvestment) {
	delete pInvestment;
}

//std::unique_ptr<Investment, void(*)(Investment* pInvestment)> ptr2(new Stock("hello"), delInv);
std::unique_ptr<Investment, decltype(&delInv)> ptr2(new Stock("hello"), delInv);
//std::unique_ptr<Investment> ptr3(new Stock("hello"), delInv);
//std::shared_ptr<Investment> ptr4(new Stock("hello"), delInv);

std::unique_ptr<Investment> ptr4(new Stock("hello"));
std::shared_ptr<Investment> ptr5 = std::move(ptr4);