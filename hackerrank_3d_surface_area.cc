#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, total = 0;
	cin >> n >> m;
	vector<vector<int>> a(n + 2, vector<int>(m + 2, 0));
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}

	total = 2 * n * m;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			total += abs(a[i + 1][j] - a[i][j]);
			total += abs(a[i][j + 1] - a[i][j]);
		}
	}

	// OR: (but a needs to have size n x m)
	// total += 2 * n * m;
	// for (int i = 0; i < n; i++) {
	// 	total += a[i][0];
	// 	total += a[i][m - 1];
	// }

	// for (int j = 0; j < m; j++) {
	// 	total += a[0][j];
	// 	total += a[n - 1][j];
	// }

	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < m; j++) {
	// 		if (i < n - 1 and a[i + 1][j] > a[i][j]) total += a[i + 1][j] - a[i][j];
	// 		if (i < n - 1 and a[i][j] > a[i + 1][j]) total += a[i][j] - a[i + 1][j];
	// 		if (j < m - 1 and a[i][j] < a[i][j + 1]) total += a[i][j + 1] - a[i][j];
	// 		if (j < m - 1 and a[i][j + 1] < a[i][j]) total += a[i][j] - a[i][j + 1];
	// 	}
	// }

	cout << total << "\n";
}