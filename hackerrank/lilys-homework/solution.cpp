#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int swaps_to_order(vector<int> v, vector<int> &order) {
	int i, swaps=0;
	unordered_map<int, unordered_set<int>> n2idx;
	for (i=0; i<v.size(); ++i) n2idx[order[i]].insert(i);
	for (i=0; i<v.size(); ++i) {
		while (n2idx[v[i]].count(i) == 0) {
			for (auto j : n2idx[v[i]])
				if (v[i] != v[j]) {
					swap(v[i], v[j]);
					n2idx[v[i]].erase(j);
					break;
				}
			++swaps;
		}
	}
	return swaps;
}

int main() {
	int n, i, swaps=0, ascending_swaps, descending_swaps;
	cin >> n;
	vector<int> nums(n);
	for (i=0; i<n; ++i) cin >> nums[i];
	vector<int> order = nums;
	sort(order.begin(), order.end());
	ascending_swaps = swaps_to_order(nums, order);
	sort(order.begin(), order.end(), greater<int>());
	descending_swaps = swaps_to_order(nums, order);
	cout << min(ascending_swaps, descending_swaps) << endl;
	return 0;
}
