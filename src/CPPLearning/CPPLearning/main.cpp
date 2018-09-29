#define NDEBUG

#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <tchar.h>
#include <Windows.h>
#include <deque>
#include <list>
#include <stack>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>
#include <chrono>
#include <Windows.h>
#include "Quote.h"
#include "Shape.h"
#include "Animal.h"
#include "MyList.h"
#include <functional>
#include "BlobT.h"

using namespace std;

void vector_demo()
{
	vector<int> int_vec;

	for (decltype(int_vec.size()) index = 0; index < 10; index++)
	{
		int_vec.push_back(index);
	}

	for (auto val : int_vec)
	{
		std::cout << val << std::endl;
	}

	decltype(int_vec.size()) size = int_vec.size();
	std::cout << "size: " << size << std::endl;

	for (decltype(int_vec.size()) index = 0; index < size; index++)
	{
		std::cout << "element is :" << int_vec.back() << std::endl;
		int_vec.pop_back();
	}
	std::cout << "size: " << int_vec.size() << std::endl;
}

void for_range_demo()
{
	string str = "hello, world!";
	for (auto &ch : str)
	{
		ch = toupper(ch);
	}

	std::cout << str << std::endl;
}

void string_iterator_demo()
{
	string str{ "hello,world" };
	
	for (auto it = str.begin(); it != str.end(); it++)
	{
		*it = toupper(*it);
	}

	std::cout << str << std::endl;
}

void array_demo()
{
	int arr[10];

	for (int i = 0; i < 10; i++)
	{
		arr[i] = i;
	};

	int *end = &arr[10];
	for (int *idx = arr; idx != end; idx++)
	{
		std::cout << *idx << " ";
	}

	std::cout << std::endl;

}

void multi_array_demo()
{
	int a[3][4];
	
	int(*p)[4] = a;


	for (; p != p + 3; p++)
		for (int *q = *p; q != *p + 4; q++)
		{
			std::cout << *q << " ";
		}

	std::cout << std::endl;
}

int fact1(int val)
{
	if (val == 1)
		return 1;

	return val * fact1(val - 1);
}

int fact2(int val)
{
	int ret = 1;
	while (val > 1)
	{
		ret *= val;
		--val;
	}

	return ret;
}

void func_string(string s)
{
	s = "world";
}

int find_char(const string &s, char c, string::size_type &occurs){

	int ret = -1;
	for (auto i = 0; i != s.size(); ++i){
		if (s[i] == c){
			++occurs;
			if (ret == -1){
				ret = i;
			}
		}
	}
	return ret;
}

bool has_upper_letter(const string &s){
	for (const auto ch : s){
		if (isupper(ch))
			return true;
	}

	return false;
}

void to_lower(string &s){
	for (auto &ch : s){
		ch = tolower(ch);
	}
}

void assert_demo()
{
	assert(0);

	std::cerr << "error: " << __FILE__ << " : in fuction:"
		<< __FUNCTIONW__ << " : line: " << __LINE__ << std::endl;
}

typedef int (*func)(int a, int b);

void use_bigger(int a, int b, int(*foo)(int a, int b))
{

}


typedef int(*bar)(int, int);


void unsign_int_test()
{
	unsigned int a = 1;
	unsigned int b = 2;
	unsigned result = a - b;
	result = -1;
	std::cout << result << std::endl;
}

void deque_test(){

	string s;
	deque<string> mydeque;
	while (cin >>s)
	{
		mydeque.push_back(s);
	}

	auto it = mydeque.cbegin();

	auto end = mydeque.cend();

	while (it != end)
	{
		cout << *it << "\n";
		++it;
	}

	cout << endl;

}

void list_test()
{
	int val;
	list<int> mylist;
	while (cin >> val){
		mylist.push_back(val);
	}

	auto it = mylist.cbegin();
	auto end = mylist.cend();
	while (it != end){
		cout << *it << " ";
		++it;
	}

	cout << endl;
}

void vector_test()
{
	vector<int> myvector;
	int val;

	while (cin >> val){
		myvector.push_back(val);
	}

	auto begin = myvector.cbegin();
	auto end = myvector.cend();


	//往vector插入元素之后，迭代器失效
	//以下代码报错
	while (begin != end){
		myvector.insert(begin, 2 * (*begin));
		++begin;
	}

	auto size = myvector.size();
	for (int i = 0; i < size/2; ++i){
		if (myvector[i] == val){
			//todo
		}
	}
}

void vector_at_test()
{
	vector<int> myvec;
	//int ret = myvec[0];
	int ret = myvec.at(0);
	cout << ret << endl;
}

void foreach_vector(vector<int> &v){
	if (v.empty())
		return;

	for (auto b = v.cbegin(), e = v.cend(); b != e; ++b){
		cout << *b << " ";
	}
	cout << endl;
}

void vector_op_test()
{
	vector<int> test = { 1, 2, 3, 4, 5 };
	
	auto iter = test.begin();

	while (iter != test.end()){
		iter = test.insert(iter, *iter);
		iter += 2;
	}

	for (auto b = test.cbegin(), e = test.cend(); b != e; ++b){
		cout << *b << " ";
	}

	cout << endl;

	iter = test.begin();

	while (iter != test.end()){
		iter = test.erase(iter);
		++iter;
	}
	//string::npos
	foreach_vector(test);

}

void std_string_test()
{
	vector<string> v;
	for (int i = 0; i < 5; ++i){
		v.push_back(to_string(i));
	}

	int sum = 0;

	for (const auto e : v){
		sum += stoi(e);
	}

	cout << "sum is " << sum << endl;
}

//adapter containter

class MyStack{
public:
	void pop();
	void push(int value);
	typedef unsigned long size_t;
	size_t size(){ return m_vector.size(); }
	bool empty(){ return size() == 0; }
	int &top(){ return m_vector.back(); }

private:
	vector<int> m_vector;
};

void MyStack::pop(){
	if (m_vector.empty())
		throw exception("stack empty!");

	m_vector.pop_back();
}

void MyStack::push(int val)
{
	m_vector.push_back(val);
}


void stack_test()
{
	stack<int> mystack;
	for (int i = 0; i < 5; i++){
		mystack.push(i);
	}

	while (!mystack.empty())
	{
		auto value = mystack.top();
		cout << value << " ";
		mystack.pop();
	}
}

void mystack_test()
{
	MyStack istack;
	for (int i = 0; i < 5; i++){
		istack.push(i);
	}

	while (!istack.empty())
	{
		auto value = istack.top();
		cout << value << " ";
		istack.pop();
	}

	cout << "stack size is: " << istack.size() << endl;

}

void accumulate_test()
{
	vector<int> ivec = { 1, 2, 3, 4, 5 };

	int sum = accumulate(ivec.cbegin(), ivec.cend(), 0);
	cout << "sum is " << sum << endl;
	
}

void equal_test()
{
	//vector<string> fvec = { "hello", "world" };
	//vector<string> svec = { "hello", "world" };

	vector<const char*> fvec = { "hello", "world" };
	vector<const char*> svec = { "hello", "world" };

	//在使用三目运算符时，注意加上括号
	cout << "fvec " << (equal(fvec.cbegin(), fvec.cend(), svec.cbegin()) ? "is equal" : "is not equal") << " to svec" << endl;


}

void back_inserter_test()
{
	vector<int> ivec(10, 0);
	list<int> ilist;

	ivec.reserve(10);


	int val;
	while (cin>>val)
	{
		ilist.push_back(val);
	}

	copy(ilist.cbegin(), ilist.cend(), ivec.begin());
}

void sort_test()
{
	vector<int> ivec = { 1, 3, 2, 3, 10, 8 };
	for (const auto &i : ivec){
		cout << i << " ";
	}
	cout << "after sort" <<endl;

	//默认排序
	//sort(ivec.begin(), ivec.end());

	//逆序排序，使用lambda表达式
	sort(ivec.begin(), ivec.end(), [](const int &a, const int &b){ return a > b; });

	for_each(ivec.begin(), ivec.end(), [](const int &a){cout << a << " "; });

	cout << endl;

	//unique 唯一算法，会将相同的元素挪到最后，但是不会删除元素。返回重复的元素的迭代器
	//注意: 挪到最后的元素的值无法确定
	auto it = unique(ivec.begin(), ivec.end());
	ivec.erase(it, ivec.end());

	for_each(ivec.begin(), ivec.end(), [](const int &a){cout << a << " "; });


	cout << endl;
}

void stream_iterator_test()
{
	istream_iterator<int> it(cin), eof;

	vector<int> ivec;

	while (it != eof)
	{
		ivec.push_back(*it++);
	}

	ostream_iterator<int> os(cout, " ");
	//for_each(ivec.cbegin(), ivec.cend(), [&os](const int val){*os = val; });
	copy(ivec.cbegin(), ivec.cend(), os);
}

void map_test()
{
	map<string, int> imap = { {"1",1}, {"2",2} };
	
	auto it = imap.cbegin();
	while (it !=imap.cend())
	{
		auto key = it->first;
		auto val = it->second;

		cout << key << " " << val;
	}
}

void vector_test2()
{
	vector<int> ivec;
	ivec[0] = 1; //报错，因为这时ivec还是空的
}

void multiset_test()
{
	multiset<string> iset;

	iset.insert("hello");
	iset.insert("world");
	iset.insert("hello");

	auto count = iset.count("hello");
	auto it = iset.find("hello");
	while (count){
		cout << *it << " ";
		--count;
		++it;
	}

}

void cin_string_test()
{
	string s;
	while (cin>>s)
	{
		cout << s << endl;
	}
}

void getline_test()
{
	string line;
	while (getline(cin, line)){
		cout << line << endl;
	}
}


//TODO: 如果返回为引用，貌似会有问题？
const map<string, string> buildup_map(ifstream &rule)
{
	string key;
	string value;
	string line;

	map<string, string> map_rules;
	if (rule.is_open())
	{
		while (getline(rule, line))
		{
			istringstream iss(line);
			iss >> key;
			getline(iss, value);
			map_rules[key] = value.substr(1);
			//map_rules.insert(make_pair(key, value.substr(1)));
		}
		rule.close();
	}
	return map_rules;
}

const string &transform(const string &word, const map<string, string> &rules_map)
{
	auto map_it = rules_map.find(word);
	if (map_it != rules_map.cend())
	{
		return map_it->second;
	}
	else
	{
		return word;
	}
}

// iostream 不能使用const修饰
//IO 对象无拷贝或赋值，读写一个IO对象会改变其状态（状态位会改变），因此传递和返回的引用不能是const的！！
void transform_text(ifstream &input, ifstream &rule)
{
	//auto rules = buildup_map(rule);
	const int &val = 1;
	const int val2 = val;

	auto rules = buildup_map(rule);
	
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			istringstream iss(line);
			string word;
			while (iss >> word)
			{
				cout << transform(word, rules) << " ";
			}
			cout << endl;
		}
		input.close();
	}
}

void TestTransformText()
{
	transform_text(ifstream("input.txt"), ifstream("rules.txt"));
}

void error_msg(initializer_list<string> li)
{
	for (auto beg = li.begin(), end = li.end(); beg != end; ++beg)
	{
		cout << *beg << " ";
	}
	cout << endl;
}

class StrBlob
{
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> li);

	void pop_back();
	void push_back(string &s);
	size_type size() const { return ptr->size(); }

	//提供const重载，因为非常量函数对于常量对象来说是不可见的
	void pop_back() const;
	void push_back(const string &s) const;
	

private:
	shared_ptr<vector<string>> ptr;
	void check(size_type idx, const string &errmsg) const;

	//实际做事的private函数
	void do_pop_back() const;
	void do_push_back(const string &s) const;
};

StrBlob::StrBlob() : ptr(make_shared < vector<string>>()){}

StrBlob::StrBlob(initializer_list<string> li)
	: ptr(make_shared<vector<string>>(li)){}

void StrBlob::pop_back()
{
	do_pop_back();
}

void StrBlob::push_back(string &s)
{
	do_push_back(s);
}

void StrBlob::check(StrBlob::size_type idx, const string &msg) const
{
	if (idx >= size())
		throw out_of_range(msg);
}


void StrBlob::pop_back() const
{
	do_pop_back();
}

void StrBlob::push_back(const string &s) const
{
	do_push_back(s);
}

void StrBlob::do_pop_back() const
{
	check(0, "no data");
	return ptr->pop_back();
}

void StrBlob::do_push_back(const string &s) const
{
	ptr->push_back(s);
}

void const_test2()
{
	int val1 = 1024;
	const int val2 = 1024;
	int val3 = 1;
	const int val4 = 1;

	int *const p1 = &val1;
	const int *p2 = &val2;

	//p1 = &val3;  //报错，p1本身为常量指针
	*p1 = 1;  //正确

	p2 = &val1;  //正确
	//*p2 = 1;  //报错，p2指向一个常量，无法修改
}

class foo{
public:
	int get_val(){ return do_get_val(); }
	int get_val() const{ return do_get_val(); }
private:
	int val = 0;
	int do_get_val() const { return val; }
};

void shared_ptr_test()
{
	//auto p = make_shared<int>(1);
	shared_ptr<int> p(new int(42));
	int *q = p.get();
	{
		shared_ptr<int>(q);
	}
	//delete q;
	auto ret = *p;
}

void allocator_test()
{
	allocator<string> alloc;
	auto const p = alloc.allocate(10);  //定义为const，因为使用allocator的时候最后释放需要用到该指针
	auto q = p;
	alloc.construct(q++, "hello");
	alloc.construct(q++, "hello, world");
	alloc.construct(q++, 10, 'c');


	cout << *p << endl;
	//cout << *q << endl;

	while (q != p)
	{
		alloc.destroy(--q);
	}

	alloc.deallocate(p, 10);
}

class TextQuery
{
public:
	typedef vector<string>::size_type line_no;
	TextQuery();
	TextQuery(const string &filename);

	~TextQuery();
	
	void PrintSearchResult(const string &word);
	const string &GetFileName(){ return filename; }

private:
	vector<string> contents;
	const string &GetLine(const line_no lineNumber);
	void check(const line_no lineNumber, const string &errmsg);
	//c++ 有没有类似readonly
	string filename;
	void loadfile();
	set<line_no> matchedLines;
	DWORD search(const string &word);
	void print();
	string word;
};

TextQuery::TextQuery()
	: filename(){}

TextQuery::~TextQuery(){}


TextQuery::TextQuery(const string &filename)
	: filename(filename), contents()
{
	//load filename and save to contents

	loadfile();
}

void TextQuery::loadfile()
{

	ifstream input(filename);
	//如何查看ifstream的错误信息？？
	//stream 包含各种标志位来标志流操纵中是否成功，如failbit, eofbit等

	string line;
	if(input.is_open())
	{
		while (getline(input, line))
		{
			contents.push_back(line);
		}
		input.close();
	}
}

const string &TextQuery::GetLine(const TextQuery::line_no lineNumber)
{
	check(lineNumber, "out of range");
	return contents[lineNumber];
}

void TextQuery::check(const TextQuery::line_no lineNumber, const string &errmsg)
{
	if (lineNumber >= contents.size())
		throw out_of_range(errmsg);
}

void TextQuery::PrintSearchResult(const string &w)
{
	word = w;
	search(w);
	print();

}

DWORD TextQuery::search(const string &word)
{
	DWORD count = 0;
	DWORD idx = 0;

	for (auto begin = contents.cbegin(), end = contents.cend();
		begin != end; ++begin, ++idx)
	{
		if (begin->find(word) != string::npos){
			matchedLines.insert(idx);
			++count;
		}
	}

	return count;
}

void TextQuery::print()
{
	if (matchedLines.size() == 0){
		cout << "found no occurance of word: " << word << endl;
		return;
	}

	cout << "found " << matchedLines.size() << " occurance of word: " << word << endl;
	for (auto begin = matchedLines.cbegin(), end = matchedLines.cend();
		begin != end; ++begin)
	{
		cout << "\t" << "(line " << *begin + 1 << " ) "
			<< contents[*begin] << "\n";
	}
	cout << endl;
}

void TestTextQuery()
{
	TextQuery tq("text_query.txt");
	tq.PrintSearchResult("ProcPkt");
}

class numbered
{
public:
	numbered(){ time = GetTickCount(); }
	DWORD get_time(){ return time; }
	numbered(const numbered &n){ time = GetTickCount(); }

private:
	DWORD time = 0;
};

void f(numbered &s)
{
	cout << s.get_time() << endl;
}


#define MAX_PATH 256


int average(int num, ...)
{
	va_list valist;
	double sum = 0.0;
	va_start(valist, num);

	for (int i = 0; i < num; i++){
		sum += va_arg(valist, int);
	}

	va_end(valist);
	return sum / num;
}

class Test3
{
public:
	Test3(string name = string()) : m_name(name){}
	Test3(const Test3&);
	Test3& operator=(const Test3&);

private:
	string m_name;
};

Test3::Test3(const Test3& t)
{
	m_name = t.m_name;
	cout << "copy constructor called" << endl;
}

Test3& Test3::operator=(const Test3& t)
{
	m_name = t.m_name;
	cout << "assignment operator called" << endl;
	return *this;
}

class RValueTest
{
public:
	RValueTest() : data({ 1,4,2,3 }) {}
	
	RValueTest sorted() && ;
	RValueTest sorted() const &;

private:
	vector<int> data;
};

RValueTest RValueTest::sorted() &&
{
	std::sort(data.begin(), data.end());
	return *this;
}

//RValueTest RValueTest::sorted() const &
//{
//	RValueTest ret(*this);
//	std::sort(ret.data.begin(), ret.data.end());
//	return ret;
//}

//RValueTest RValueTest::sorted() const &
//{
//	RValueTest ret(*this);
//	return ret.sorted();
//}

RValueTest RValueTest::sorted() const &
{
	return RValueTest(*this).sorted();
}

void test_rvalue()
{
	RValueTest rv1;
	auto tmp = rv1.sorted();  //lvalue reference

	auto tmp2 = std::move(rv1).sorted();  //rvalue reference
}

void badcode_test_shape()
{
	//following is bad code, use new to allocate memory which is unnecessary
	Shape *s = new SRegtangel(2, 3);
	auto t1 = s->area();

	delete s;

	Shape *s2 = new SCircle(2);
	auto t2 = s2->area();
	delete s2;
}

void goodcode_test_shape()
{
	SRegtangel sr(2, 3);
	SCircle sc(2);

	Shape &s = sr;
	cout << s.area() << endl;
	Shape &s2 = sc;
	cout << s2.area() << endl;

}

void test_animal()
{
	Animal ani;
	Dog dog;

	Animal &a = dog;
	Animal *d = &dog;

	a.print();
	d->print();

	ani.print();
	dog.print();
}

template <typename T>
int compare(const T& t1, const T& t2)
{
	if(t1 < t2)
		return -1;
	if (t1 == t2) return 0;
	if (t1 > t2) return 1;
}


//using function template
//template<typename T> typename foo(T &, T &) {}

template<typename T> void print_c(vector<T> &vec)
{
	for (auto i = 0; i != vec.size(); ++i)
	{
		/*T ele = vec[i];
		std::cout << ele << std::endl;*/
		std::cout << vec[i] << std::endl;
	}
}

template<typename T> void print_d(vector<T> &vec)
{
	for (auto begin = vec.cbegin(), end = vec.cend(); begin != end;++begin) {
		std::cout << *begin << std::endl;
	}
}

template<typename T, std::size_t N>
class Array
{
public:
	Array<T, N>() {}
	std::size_t size() { return m_size; }
	T &operator[](const int idx)
	{
		return m_arr[idx];
	}

private:
	std::size_t m_size;
	T m_arr[N];
};

//TODO: count if wrong
//
//void test()
//{
//	vector<int> myvec = { 1,2,3,4,5 };
//	greater<int> gt;
//	auto cnt = count_if(myvec.cbegin(), myvec.cend(), [](const int a) {return a > 3;});
//	cnt = count_if(myvec.cbegin(), myvec.cend(), std::greater<int>());
//	std::for_each(myvec.begin(), myvec.end(), [](int &a) { a = a * 2;});
//}

//class Debuggable
//{
//private:
//	ostream& os;
//
//public:
//	Debuggable(ostream& s = std::cerr) : os(s) {}
//	template<typename T> void operater()(T *p) const{
//		os << "delete" << std::endl;
//		delete p;
//	}
//};

class twotimes
{
public:
	int operator()(int a)
	{
		return a * 2;
	}
};

//template<typename T>
//int compare(const T a1, const T a2)
//{
//	return a1 > a2;
//}

void test_template_deduction()
{
	compare("dad", "mom");
	//compare("aka", "ms");
}

void seek_tell_test()
{

	fstream inout("test.txt", std::fstream::ate | std::fstream::in | std::fstream::out);
	if (!inout) {
		cerr << "failed to open test.txt" << endl;
		return;
	}

	auto end_mark = inout.tellg();
	inout.seekp(0, fstream::beg);
	size_t cnt = 0;
	string line;

	while (inout && inout.tellg() != end_mark
		&& getline(inout, line)) {
		cnt += line.size() + 1; //add 1 for newline character
		auto mark = inout.tellg();
		inout.seekp(0, fstream::end);
		inout << cnt;
		if (mark != end_mark) {
			inout << " ";
		}
		inout.seekg(mark);
	}

	inout.seekp(0, fstream::end);
	inout << "\n";
}

template<typename T> void myprint(const T& t) {
	std::cout << t << std::endl;
}

void test_blob_template() {
	Blob<int> ia;
	Blob<int> ib = { 1,2,3,4,5 };

	auto value = ib.back();
	myprint(value);

	Blob<string> ic = { "hello", "world" };
	myprint(ic[1]);
}

#include <array>

void test_std_array() {
	std::array<int, 3> a2 = { 1, 2, 3 };
}

void test_known_type() {
	auto x = 1;
	auto& y = x;
	const auto& z = x;

	//使用typeid来获取推导的类型并不可靠，可以使用boost库来达到这个目的
	myprint(typeid(x).name());
	myprint(typeid(y).name());
	myprint(typeid(z).name());
	//std::cout << typeid(x).name() << std::endl;
	//std::cout << typeid(y).name() << std::endl;
}


//template<typename... Args>
//void MyOutputDebugStr(Args... args) {
//
//}

void Myoutputdebugstr(const char* format, ...) {
	va_list	args;
	va_start(args, format);
	char buf[512];
	int n = vsprintf_s(buf, format, args);
	buf[n] = '\n';
	buf[n+1] = '\0';
	OutputDebugString(buf);
}

void test_output_debug_str() {
	OutputDebugString("robert age is 24");
	Myoutputdebugstr("%s age is %d", "robert", 12);
	Myoutputdebugstr("hello world!");
}

int main(void)
{
	test_output_debug_str();
	std::cin.get();
}