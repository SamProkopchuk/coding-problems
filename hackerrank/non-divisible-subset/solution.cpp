#include<iostream>
#include<unordered_map>

using namespace std;

int main() {
	int n, mod, temp, res;
	cin >> n >> mod;
	unordered_map<int, int> remcount;
	for (int posrem = 0; posrem < mod; posrem++) {
		// Simple defaultdict-like behavior
		remcount[posrem] = 0;
	}
	for (int c=0; c<n; c++) {
		cin >> temp;
		remcount[temp % mod] += 1;
	}
	res = (remcount[0] > 0) + (mod % 2 == 0 && remcount[mod / 2]);
	for (int rem=1; rem<(mod+1)/2; rem++) {
		res += max(remcount[rem], remcount[mod-rem]);
	}
	cout <<  res << endl;
	return 0;
}
