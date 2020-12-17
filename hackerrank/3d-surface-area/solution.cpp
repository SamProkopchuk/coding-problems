#include<iostream>
#include<cmath>

using namespace std;

int main() {
	int h, w, sa, v;
	cin >> h >> w;
	int* matrix = new int[h * w];
	for (int idx=0; idx<h*w; idx++) {
		cin >> matrix[idx];
	}
	sa = 2 * h * w;
	for (int r=0; r<h; r++) {
		for (int c=0; c<w; c++) {
			v = matrix[r * w + c];
			sa += r ? abs(v - matrix[(r-1) * w + c]) : v;
			sa += c ? abs(v - matrix[r * w + c - 1]) : v;
			if (r == h-1) sa += v;
			if (c == w-1) sa += v;
		}
	}
	cout << sa << endl;
	return 0;
}
