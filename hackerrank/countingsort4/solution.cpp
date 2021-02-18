#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

struct item {
	int i;
	string s;
	bool dash;
};

int cmp(const item& a, const item& b) {
	return a.i < b.i;
}

int main() {
	int n;
	cin >> n;
	vector<item> v(n);

	for (int i=0; i<n; ++i) {
		cin >> v[i].i;
		cin >> v[i].s;
		v[i].dash = i < n / 2;
	}

	stable_sort(v.begin(), v.end(), cmp);

	for (item it : v) cout << (it.dash ? "-" : it.s) << " ";
	cout << endl;

	return 0;
}