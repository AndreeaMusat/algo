/*
	Author: Andreea Musat
	Date: 16 sept 2017

	https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1662
*/
#include <bits/stdc++.h>
using namespace std;

long long dp[51][51];

long long solve(int n, int m, int k)
{
	memset(dp, 0, sizeof dp);

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= k; j++)
		{
			/* Base case: no unit, no bar => one way of doing this */
			if (i == 0 && j == 0)
				dp[i][j] = 1;

			/* Otherwise at each step try to make a bar from k 
			   units (with k less than or equal to m */
			for (int k = 1; k <= m; k++)
			{
				if (i - k >= 0)
					dp[i][j] += dp[i - k][j - 1];
				else
					break;	
			}
		}
	}

	return dp[n][k];
}

int main()
{
	int n, m, k;
	while (cin >> n >> k >> m)
	{
		long long result = solve(n, m, k);
		cout << result << "\n";
	}
}
