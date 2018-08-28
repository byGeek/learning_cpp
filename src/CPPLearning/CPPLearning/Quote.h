#include<string>

class Quote{
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price) :
		bookNo(book), price(sales_price){}

	const std::string isbn() const { return bookNo; }

	virtual double get_total_price(size_t n) const{
		return n*price;
	}

	virtual ~Quote() = default;

private:
	std::string bookNo;

protected:

	double price = 0.0;


};

class Dire_quote : public Quote
{
public:
	Dire_quote() = default;
	Dire_quote(const std::string &book_num, double price, size_t size, double discount) :
		Quote(book_num, price), quentity(size), discount(discount)
	{}

	double get_total_price(size_t n) const = 0;

protected:
	size_t quentity;
	double discount;
};