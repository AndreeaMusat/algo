#include <bits/stdc++.h>
using namespace std;

bool operator==(const vector<long long>& v1, const vector<long long>& v2) {
	if (v1.size() != v2.size()) return false;
	for (size_t i = 0; i < v1.size(); i++)
		if (v1[i] != v2[i]) return false;
	return true;
}

int main() {
	int q, n, x;
	vector<long long> row_counts;
	vector<long long> col_counts;

	ios_base::sync_with_stdio(false);
	cin >> q;
	while (q--) {
		cin >> n;

		row_counts.assign(n, 0);
		col_counts.assign(n, 0);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> x;
				row_counts[i] += x;
				col_counts[j] += x;
			}
		}

		sort(row_counts.begin(), row_counts.end());
		sort(col_counts.begin(), col_counts.end());

		cout << (row_counts == col_counts ? "Possible\n" : "Impossible\n");
	}
}