/*
	Author: Andreea Musat
	Date: 26 Sept 2017

	Get nth (unique) rational numbers (ordered in a spiral)
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=434
*/
#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> solve(int n)
{
	vector<pair<int, int>> ans;
	vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	unordered_set<double> unique;

	int x = 0, y = 0;
	int dir_idx = 0, len = 1;
	int cnt = 0, taken = 0;

	while (true)
	{
		if (ans.size() == n + 1)
			break;

		x += dirs[dir_idx].first;
		y += dirs[dir_idx].second;

		if (x != 0 && unique.find(double(y) / double(x)) == unique.end())
		{
			unique.insert(double(y) / double(x));
			if (x < 0 && y > 0) 
				ans.push_back(make_pair(-x, -y));
			else
				ans.push_back(make_pair(x, y));
		}
		taken += 1;
		if (taken == len)
		{
			taken = 0;
			cnt = (cnt + 1) % 2;
			if (cnt == 0) len += 1;
			dir_idx = (dir_idx + 1) % 4;
		}
	}

	return ans;
}

int main()
{
	int n, max_in = INT_MIN;
	vector<int> input;

	while (cin >> n)
	{
		input.push_back(n);
		max_in = max(max_in, n);
	}		

	vector<pair<int, int>> ans = solve(max_in);
	for (size_t i = 0; i < input.size(); i++)
	{
		cout << ans[input[i]].second << " / " 
		     << ans[input[i]].first << "\n";
	}

	return 0;
}
