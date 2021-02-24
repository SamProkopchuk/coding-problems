#include<iostream>
#include<string>
#include<cstring>


using namespace std;

int mem[5001][5001];

int common_child_size(string &a, string &b, int ai=0, int bi=0) {
	if (ai == a.size() || bi == b.size()) return 0;
	if (a[ai] == b[bi]) return 1 + common_child_size(a, b, ai+1, bi+1);
	if (mem[ai+1][bi] == -1)
		mem[ai+1][bi] = common_child_size(a, b, ai+1, bi);
	if (mem[ai][bi+1] == -1)
		mem[ai][bi+1] = common_child_size(a, b, ai, bi+1);
	return max(mem[ai+1][bi], mem[ai][bi+1]);
}

int main() {
	string a, b;
	cin >> a >> b;
	memset(mem, -1, sizeof(mem));
	cout << common_child_size(a, b) << endl;
	return 0;
}
