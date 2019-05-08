/*
dynamic programming algorithm

动态规划算法

*/

#include <iostream>
#include <cassert>
#include <stdio.h>
#include <vector>
#include <cmath>

using namespace std;

/*
febnachi sequence

n=1,2,...,n
f(n) = 1,1,2,3,...,f(n-2) +f(n-1)

*/

/*
using recurrsion

*/
int fn_recurrsion(int n) {
	if (n <=2) {
		return 1;
	}

	return fn_recurrsion(n - 1) + fn_recurrsion(n - 2);
}


/*
using dynamic programming
trade space for time


msvc does not support vari-length array
gcc does

ref: https://stackoverflow.com/questions/33423502/expression-did-not-evaluate-to-a-constant-c
*/

int fn_dp1(const int n) {
	int* pfn = new int[n];

	int* temp = pfn;

	*temp++ = 1;
	*temp++ = 1;

	for (int i = 3; i <= n; ++i) {
		*temp++ = *(temp - 1) + *(temp - 2);
	}

	int ret = *(temp - 1);
	delete[] pfn;
	return ret;
}


/*
actually we do not need extral space
*/
int fn_dp2(int n) {
	if (n <= 2) {
		return 1;
	}

	int tn_2 = 1;
	int tn_1 = 1;
	int tn = 0;

	for (int i = 3; i <= n; ++i) {
		tn = tn_1 + tn_2;
		tn_2 = tn_1;
		tn_1 = tn;
	}

	return tn;
}

/*
int fib(int n)
{
	int f[n + 1];
	int i;
	f[0] = 0;   f[1] = 1;
	for (i = 2; i <= n; i++)
		f[i] = f[i - 1] + f[i - 2];

	return f[n];
}
*/

void test_fib() {
	int r1 = fn_recurrsion(40);
	int r2 = fn_dp1(40);
	int r3 = fn_dp2(40);

	assert(r1 == r2);
	assert(r1 == r3);
}

bool isUglyNumber(int n) {
	while (n % 2 == 0) {
		n = n / 2;
	}

	while (n % 3 == 0) {
		n = n / 3;
	}

	while (n % 5 == 0) {
		n = n / 5;
	}

	return n == 1 ? true : false;
}

int find_nth_ugly_number(int n) {

	if (n == 1) {
		return 1;
	}

	int i = 2;
	int cnt = 1;

	while (true) {
		if (isUglyNumber(i)) {
			++cnt;
			if (cnt == n) {
				break;
			}
		}

		++i;
	}

	return i;
	
}

/*
use dynamic programming
*/

int min(int a, int b, int c) {
	return (a < (b < c ? b : c) ? a : (b < c ? b : c));
}
int findUglyNumber(int n) {
	int* ugly = new int[n];
	int* t = ugly;

	*ugly = 1;

	int r2 = 0, r3 = 0, r5 = 0;
	int next_multiply_2 = 2;
	int next_multiply_3 = 3;
	int next_multiply_5 = 5;

	int ugly_num = 1;
	int i = 1;
	for (; i < n; ++i) {
		ugly_num = min(next_multiply_2, next_multiply_3, next_multiply_5);

		*(ugly + i) = ugly_num;

		/*
		if any two of multiply is equal, both got incremented
		*/
		if (ugly_num == next_multiply_2) {
			++r2;
			next_multiply_2 = *(ugly+r2) * 2;
		}

		if (ugly_num == next_multiply_3) {
			++r3;
			next_multiply_3 = *(ugly+r3) * 3;
		}

		if(ugly_num == next_multiply_5)
		{
			++r5;
			next_multiply_5 = *(ugly+r5) * 5;
		}
	}

	delete[] ugly;
	return ugly_num;
}



void test_ugly_number() {
	assert(findUglyNumber(2) == 2);
	assert(findUglyNumber(3) == 3);
	assert(findUglyNumber(4) == 4);
	assert(findUglyNumber(5) == 5);
	assert(findUglyNumber(6) == 6);
	assert(findUglyNumber(7) == 8);
	assert(findUglyNumber(8) == 9);
	assert(findUglyNumber(9) == 10);
	assert(findUglyNumber(10) == 12);
	assert(findUglyNumber(11) == 15);
	assert(findUglyNumber(12) == 16);
	assert(findUglyNumber(13) == 18);
}

/*
output all subsequence
output len size subsequence
*/
vector<vector<int>> get_sub_sequence(vector<int>& seq, int len) {
	int size = seq.size();

	vector<vector<int>> ret;

	for (int i = 0; i <= size - len; ++i) {

	}

	return ret;
}

/*
sub array must be continuous
while sub sequence not
*/

vector<vector<int>> get_all_sub_array(vector<int>& seq) {
	int size = seq.size();

	vector<vector<int>> ret;

	for (int i = 0; i < size; ++i) {  //start point
		for (int len = 1; len <= size - i; ++len) {//len

			vector<int> v;
			for (int k = i; k < len + i; ++k) {
				v.push_back(seq[k]);
			}
			ret.push_back(v);
		}
	}

	return ret;
}

/*
get all subsequence
use power set, ref: https://www.geeksforgeeks.org/power-set/
ref: https://en.wikipedia.org/wiki/Power_set

*/
vector<vector<int>> get_all_sub_sequence(vector<int>& seq) {
	vector<vector<int>> ret;

	int power_size = pow(2, seq.size());

	for (int i = 0; i < power_size; ++i) {
		vector<int> v;
		for (int j = 0; j < seq.size(); ++j) {
			if (i & (1 << j)) {
				v.push_back(seq[j]);
			}
		}
		ret.push_back(std::move(v));
	}

	return ret;
}

/*
print all sequence at given length

input: 1,2,3, len = 2
return:
	1,2
	1,3
	2,3
*/

vector<vector<int>> get_sequences(vector<int>& seq, int len) {
	vector<vector<int>> ret;




	return ret;
}

int main() {

	//test_ugly_number();
	vector<int> v{ 1,2,3,4 };
	auto r1 = get_all_sub_array(v);
	auto r2 = get_all_sub_sequence(v);

}