/*
divide and conquer

分治算法

将将问题分成一些小的问题，求解小的问题，最后再merge成整个的解决方案。

归并排序是分治算法的一个实际应用

归并排序有两种实现方式：

1) top-down: 递归方式
2) bottom-up: 迭代方式
*/

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void my_merge_sort(int arr[], int start, int end, int working_arr[]);


void do_merge(int arr[], int start, int mid, int end, int working_arr[]) {
	int i = start;
	int j = mid + 1;

	int k = 0;

	while (i <= mid && j <= end) {
		if (arr[i] < arr[j]) {
			working_arr[k++] = arr[i++];
		}
		else {
			working_arr[k++] = arr[j++];
		}
	}

	while (i <= mid) {
		working_arr[k++] = arr[i++];
	}

	while (j <= end) {
		working_arr[k++] = arr[j++];
	}

	k = 0;

	while (start<=end) {
		arr[start++] = working_arr[k++];
	}
}

void my_merge_sort(int arr[], int start, int end, int working_arr[]) {
	if (start < end) {
		int mid = (start + end) / 2;

		my_merge_sort(arr, start, mid, working_arr);
		my_merge_sort(arr, mid + 1, end, working_arr);
		do_merge(arr, start, mid, end, working_arr);
	}
}

void merge(vector<int>& v, int begin, int mid, int end, vector<int>& wv) {

	int i = begin;
	int j = mid + 1;

	int k = begin;
	while (i <= mid && j <= end) {
		if (v[i] <= v[j]) {
			wv[k++] = v[i++];
		}
		else {
			wv[k++] = v[j++];
		}
	}

	while (i <= mid) {
		wv[k++] = v[i++];
	}

	while (j <= end) {
		wv[k++] = v[j++];
	}

	while (begin <= end) {
		v[begin++] = wv[begin];
	}
}

void mergesort(vector<int>& v, int begin, int end, vector<int>& wv) {
	if (begin < end) {
		int mid = (begin + end) / 2;
		mergesort(v, begin, mid, wv);
		mergesort(v, mid + 1, end, wv);
		merge(v, begin, mid, end, wv);
	}
}



void test_mergesort() {

	int arr[] = { 1,7,2,3,1 };
	int len = sizeof(arr) / sizeof(int);
	int* working_arr = new int[len];
	my_merge_sort(arr, 0, sizeof(arr) / sizeof(int) - 1, working_arr);

}

void test_merge() {
	vector<int> v{ 1,7,2,3,1 };
	vector<int> wv(v.size());
	mergesort(v, 0, v.size()-1, wv);
}


/*
v中每个int不能重复, 且每个数都是自然数(>=0)

ref: 来自于编程之美第一章电话号码排序
*/
void bit_vector_sort(vector<int>& v) {
	int size = v.size();

	int max = 0;
	for (auto i : v) {
		if (i > max) {
			max = i;
		}
	}

	char* str = new char[max];
	char* temp = str;

	for (int i = 0; i < max; ++i) {
		*(temp++) = '0';
	}

	temp = str;

	for (int i = 0; i < size; ++i) {
		*(temp + v[i]) = '1';
	}

	for (int i = 0; i <= max; ++i) {
		if (*(temp++) == '1') {
			cout << i << " ";
		}
	}
	cout << endl;

}

int main() {
	//test_mergesort();
	//test_merge();

	vector<int> v{ 12, 32, 2, 9, 5, 7 };
	bit_vector_sort(v);

}