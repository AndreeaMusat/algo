/*
	Author: Andreea Musat 
	Date: 15 sept 2017

	Coin change variant
	
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1247
*/

#include <bits/stdc++.h>
using namespace std;

int dp[310][310];
int sum;

inline int sq(int x, int y)
{
	return x * x + y * y;
}

int coinChange(const vector<pair<int, int>>& coins, int x, int y)
{
	if (sum - sq(x, y) < 0)
		return INT_MAX;

	if (sum - sq(x, y) == 0)
		return 0;

	int& ans = dp[x][y];
	if (ans != -1)
		return ans;

	ans = INT_MAX;

	for (size_t i = 0; i < coins.size(); i++)
	{
		int res = coinChange(coins, x + coins[i].first, y + coins[i].second);
		if (res != INT_MAX)
			ans = min(ans, 1 + res);
	}

	return ans;
}

int main()
{
	int n, m, s;
	vector<pair<int, int>> coins;
	cin >> n;

	while (n--)
	{
		cin >> m >> s;
		
		if (coins.size() > 0)
			coins.clear();
		coins.resize(m);

		memset(dp, -1, sizeof dp);
		
		for (int i = 0; i < m; i++)
			cin >> coins[i].first >> coins[i].second;
		
		sum = s * s;
		int res = coinChange(coins, 0, 0);
		if (res != INT_MAX) 
			cout << res << "\n";
		else
			cout << "not possible\n";
	}
}
