//
//#include "StrVec.h"
//
//StrVec::StrVec(const StrVec & vec)
//{
//	auto p = alloc_n_copy(vec.begin(), vec.end());
//	elements = p.first;
//	cap = first_free = p.second;
//}
//
//StrVec &StrVec::operator=(const StrVec &rhs)
//{
//	/*auto data =alloc.allocate(rhs.capacity());
//	auto newele = data;
//	for (auto ptr = rhs.elements; ptr != rhs.first_free; ++ptr){
//		alloc.construct(data++, *ptr);
//	}
//	free();
//	elements = newele;
//	first_free = data;
//	cap = newele + rhs.capacity();
//	return *this;*/
//
//	auto p = alloc_n_copy(rhs.begin(), rhs.end());
//	free();
//	elements = p.first;
//	first_free = p.second;
//	cap = p.second;
//	return *this;
//
//}
//
//std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string* begin,
//	const std::string* end)
//{
//	auto data = alloc.allocate(end - begin);
//	return std::make_pair(data, std::uninitialized_copy(begin, end, data));
//}
//
//void StrVec::push_back(const std::string &str)
//{
//	chk_n_alloc();
//	alloc.construct(first_free++, str);
//}
//
//void StrVec::free()
//{
//	if (elements){
//		for (auto ptr = first_free; ptr != elements;/*blank*/){
//			alloc.destroy(--ptr);
//		}
//		alloc.deallocate(elements, cap - elements);
//	}
//}
//
//void StrVec::reallocate()
//{
//	auto newcapacity = size() ? 2 * size() : 1;
//	auto newdata = alloc.allocate(newcapacity);
//	auto newelements = newdata;
//	for (auto el = elements; el != first_free; ++el){
//		//alloc.construct(newptr++, *el);
//		alloc.construct(newdata++, std::move(*el));//std::move
//	}
//	free();  //free memory
//	elements = newelements;
//	first_free = newdata;
//	cap = newelements + newcapacity;
//}
//
//
