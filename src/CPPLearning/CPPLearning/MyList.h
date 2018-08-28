#pragma once

template<typename T> class ListItem;
template<typename T> class MyList
{
public:

	MyList<T>();
	MyList<T>(const MyList<T> &);
	~MyList();
	MyList<T> &operator=(const MyList<T> &);
	void insert(ListItem<T> *ptr, T value);

private:
	ListItem<T> * front, *rear;
};
