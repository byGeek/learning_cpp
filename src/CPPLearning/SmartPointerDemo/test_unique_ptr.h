#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <unordered_map>

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

	void foo(){}

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

void foo() {
	std::shared_ptr<Investment> ptr(new Stock("hello"));
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


class Widget : public std::enable_shared_from_this<Widget>
{
public:

	Widget() = default;
	~Widget() {
		std::cout << "widget: " << this << " deleted!" << std::endl;
	}

	void process() {
		m_processed_widgets.emplace_back(shared_from_this());
	}

private:
	std::vector<std::shared_ptr<Widget>> m_processed_widgets;
};

void test_shared_this_exception() {
	
	/*Widget* pw = new Widget();
	delete pw;
	delete pw;*/

	std::shared_ptr<Widget> w = std::make_shared<Widget>();
	w->process();

	//undefined behavior happen
	//because we create two control block for w
}

void move_up(std::unique_ptr<Stock>& up) {
	up->foo();
}

void move_ap(std::auto_ptr<Stock> ap) {
	ap->foo();
}

void test_auto_ptr() {

	//auto_ptr is deprected
	/*
	auto_ptr was created when c98 has no move sematics
	so it use copy to simulate move sematics

	unique_ptr has no copy assign operator and copy ctor
	*/

	std::auto_ptr<Stock> ap(new Stock("hello"));
	std::auto_ptr<Stock> ap2 = ap;  //legal, but not legal when using unique_ptr

	//move_ap(ap2);
	ap->foo();  //crash because ap2 is set to NULL

	std::unique_ptr<Stock> up(new Stock("hello"));
	move_up(up);
	std::unique_ptr<Stock> up1 = std::move(up);  //transfer ownership, and up is empty, can not use it again

	up->foo(); //undefined behavior!!
}


void test_weak_ptr() {
	std::shared_ptr<Stock> sp = std::make_shared<Stock>("hello");
	std::cout << sp.use_count() << std::endl;

	std::weak_ptr<Stock> wp = sp;
	std::cout << sp.use_count() << std::endl;
	std::cout << wp.use_count() << std::endl;

	std::weak_ptr<Stock> wp2 = wp;
	std::cout << wp.use_count() << std::endl;
	std::cout << wp2.use_count() << std::endl;

	std::shared_ptr<Stock> sp2 = wp.lock();
	if (sp2) {
		//sp2 not null
	}
	else {
		//sp2 null, mean weak_ptr is expired
	}

	//wp.expired can also do the test, but test 
}

std::shared_ptr<Widget> loadWidget() {
	return std::make_shared<Widget>();
}

std::shared_ptr<Widget> fast_load_widget(int id) {
	static std::unordered_map<int, std::weak_ptr<Widget>> cache;

	auto sp = cache[id].lock();  //check if exist in cache
	if (!sp) {
		sp = loadWidget();
		cache[id] = sp;  //put to cache
	}

	return sp;
}

class Observer {
public:
	void DoStuff() {
		std::cout << "Got notified" << std::endl;
	}
};

class Subject {
public:
	void Notify() {
		for (auto& ob : m_obs) {
			auto sp = ob.lock();  //convert to shared_ptr
			if (sp) {  //test if converted shared_ptr is valid
				sp->DoStuff();
			}
		}
	}

	void AddToObserver(std::weak_ptr<Observer>& ob) {
		m_obs.push_back(ob);
	}

private:
	std::vector<std::weak_ptr<Observer>> m_obs;
};

void test_observer_pattern_using_weak_ptr() {
	Subject s;
	
	auto sp = std::make_shared<Observer>();  //make a shared_ptr obj
	std::weak_ptr<Observer> ob1 = std::make_shared<Observer>();  //make a temp shared_ptr, after the assignment, shared_ptr is deleted
	std::weak_ptr<Observer> ob2(sp);

	s.AddToObserver(ob1);
	s.AddToObserver(ob2);

	s.Notify();
}

void test_pass_shared_ptr(std::shared_ptr<Stock>& sp) {
	//
}

void test_normal_func(const Stock& s) {
	const Stock& ss = s;
}