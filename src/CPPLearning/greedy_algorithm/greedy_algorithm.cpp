
/*
贪心算法总是作出在当前看来最好的选择。也就是说贪心算法并不从整体最优考虑，
它所作出的选择只是在某种意义上的局部最优选择。当然，希望贪心算法得到的
最终结果也是整体最优的。虽然贪心算法不能对所有问题都得到整体最优解，
但对许多问题它能产生整体最优解。如单源最短路经问题，最小生成树问题等。
在一些情况下，即使贪心算法不能得到整体最优解，其最终结果却是最优解的很好
近似。
*/


/*
Input:
  Items as (value, weight) pairs
  arr[] = {{60, 10}, {100, 20}, {120, 30}}
  Knapsack Capacity, W = 50;
Output:
  Maximum possible value = 220
  by taking items of weight 20 and 30 kg

*/


/*
if item can not be divided, then the greedy algorithm result
may not be the best solution
*/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


class item {
public: 
	int value;
	int weight;
public:
	item(int value, int weight): value(value), weight(weight){}
};

int backpack_problem(vector<item>& items) {
	int ret = 0;

	sort(begin(items), end(items), [](const item a, const item b) {
		double r1 = a.value / a.weight;
		double r2 = b.value / b.weight;

		return r1 > r2;
	});

	int total_weight = 50;  //backpack totol weight
	int current_weight = 0;

	for (int i = 0; i < items.size(); ++i) {
		if (current_weight + items[i].weight <= total_weight) {
			current_weight += items[i].weight;
			ret += items[i].value;
		}
		else {
			int remain = total_weight - current_weight;
			ret += remain * (items[i].value / items[i].weight);   //item can be divided
			break;
		}
	}

	return ret;
}

/*
if item can not be divided?
find a solution to get maximum value?
*/




int main() {
	vector<item> items;
	items.emplace_back(60, 10);
	items.emplace_back(100, 20);
	items.emplace_back(120, 30);

	int ret_value = backpack_problem(items);

	system("pause");
}