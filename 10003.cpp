/*
	Author: Andreea Musat
	10 feb 2018
*/

#include <bits/stdc++.h>
using namespace std;
const int MD = 64;
vector<int> cut_point;
long long memo[MD][MD];

int solve(int i, int j)
{
	if (memo[i][j] != -1)
	{
		return memo[i][j];
	}

	if (i + 1 >= j)
	{
		memo[i][j] = 0;
		return 0;
	}

	long long best = LLONG_MAX;
	long long curr = 0;

	for (int k = i + 1; k <= j - 1; k++)
	{
		curr = cut_point[j] - cut_point[i];
		curr += solve(i, k) + solve(k, j);
		best = min(best, curr);
	}
	
	memo[i][j] = best;
	return best;
}

int main()
{
	int l, n, i;
	while (true)
	{
		cin >> l;
		if (l == 0) break;
		
		cin >> n;
		
		memset(memo, -1, sizeof(memo));

		cut_point.clear();
		cut_point.resize(n + 2);
		cut_point[0] = 0;
		cut_point[n + 1] = l;

		for (i = 1; i <= n; i++)
			cin >> cut_point[i];

		cout << "The minimum cutting is " << solve(0, n + 1) << ".\n";
	}
	return 0;
}