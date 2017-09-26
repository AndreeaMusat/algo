/*
	Author: Musat Andreea
	Date: 26 Sept 2017

	Largest sequence of consecutive integers having given sum
	https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2221
*/

#include <bits/stdc++.h>
using namespace std;

pair<int, int> solve(int n)
{
	int max_seq_len = (int)sqrt(2 * n);
	for (int len = max_seq_len; len >= 1; len--)
	{
		double x = (2.0 * n / len + 1 - len) / 2;
		if (x == floor(x))
		{
			return make_pair(x, x + len - 1);
		} 
	}

	return make_pair(INT_MIN, INT_MIN);
}

int main()
{
	int n;
	while (true)
	{
		cin >> n;
		if (n == -1)
			break;

		pair<int, int> res = solve(n);
		cout << n << " = " << res.first << " + ... + " << res.second << "\n";
	}
}
