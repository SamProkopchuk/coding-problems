#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, score;

	cin >> n;
	vector<int> leaderboard;
	for (int i=0; i<n; i++) {
		cin >> score;
		if (leaderboard.empty() || score != leaderboard.back())
			leaderboard.push_back(score);
	} // leaderboard now has no duplicates.

	cin >> n;
	vector<int> alice_scores(n);
	for (int idx=0; idx<n; idx++) {
		cin >> alice_scores[idx];
	}

	for (int ascore : alice_scores) {
		while (leaderboard.size() && leaderboard.back() <= ascore) {
			leaderboard.pop_back();
		}
		cout << leaderboard.size() + 1 << endl;
	}
	return 0;
}
