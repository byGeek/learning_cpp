//#ifndef _STR_VEC_H_
//#define _STR_VEC_H_
//
//#include <string>
//#include <utility>
//
//class StrVec
//{
//public:
//	StrVec() :
//		elements(nullptr), first_free(nullptr), cap(nullptr){}
//	StrVec(const StrVec&);
//	StrVec &operator=(const StrVec &);
//	~StrVec();
//
//	size_t size() const{ return first_free - elements; }
//	size_t capacity() const { return cap - elements; }
//	void push_back(const std::string &);
//	std::string *begin() const{ return elements; }
//	std::string *end() const{ return first_free; }
//
//
//
//private:
//	std::string *elements;
//	std::string *first_free;
//	std::string *cap;
//
//	void free();
//	static std::allocator<std::string> alloc;
//	void reallocate();
//	void chk_n_alloc(){ if (size() == capacity()) reallocate(); }
//	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
//
//};
//
//#endif