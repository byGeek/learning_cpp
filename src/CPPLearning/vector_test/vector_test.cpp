#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

int main() {
	std::vector<int> v{ 1,2,3,2,3,1,4 };

	std::sort(std::begin(v), std::end(v));

	auto last = std::unique(std::begin(v), std::end(v));
	auto value = *last;

	auto it = v.erase(last, std::cend(v));
	assert(it == std::cend(v));
	//v.resize(last - std::cbegin(v));

	std::vector<int> v1{ 1,2,3,4 };

	v1.erase(std::begin(v1) + 1, std::begin(v1) + 2);  /*only delete element 2*/

	for (auto& ent : v1) {
		printf("%d ", ent);
	}
}