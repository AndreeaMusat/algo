/*
  Author: Andreea Musat
  Date: 15 sept 2017
  
  https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=503
*/

#include <bits/stdc++.h>
using namespace std;

int dp[128][(1 << 16)];

/* Top down knapsack for half of the total sum */
int knapsack(const vector<int>& arr, int n, int w)
{
	if (n == 0 || w == 0)
		return 0;

	if (dp[n][w] != 0)
		return dp[n][w];

	int& ans = dp[n][w];

	if (arr[n - 1] > w)
		return ans = knapsack(arr, n - 1, w);

	return ans = max(knapsack(arr, n - 1, w), 
			   knapsack(arr, n - 1, w - arr[n - 1]) + arr[n - 1]);

}

int main()
{
	int n, m, total_sum;
	vector<int> arr; cin >> n;
	while (n--)
	{
		cin >> m;
		if (arr.size() > 0) 
			arr.clear();
		arr.resize(m); 
		total_sum = 0;
		memset(dp, 0, sizeof dp);

		for (int i = 0; i < m; i++) 
		{
			cin >> arr[i];
			total_sum += arr[i];
		}
		cout << total_sum - 2 * knapsack(arr, m, total_sum / 2) << "\n";
	}

	return 0;
}
