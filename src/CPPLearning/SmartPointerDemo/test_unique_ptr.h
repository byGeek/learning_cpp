#pragma once
#include <iostream>
#include <memory>

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
	std::unique_ptr<Stock> stock(new Stock("hello"));
	return stock;

	//in c++ 14
	//return std::make_unique<Stock>("hello");
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