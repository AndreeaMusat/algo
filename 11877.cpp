/*
	Author: Andreea Musat
	Date: 25 Sept 2017

	Some simple mathematical simulation
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2999
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, ans = 0;
	while (true)
	{
		cin >> n;
		if (n == 0)
			break;
		ans = 0;
		while (n >= 3)
		{
			ans += (n - (n % 3)) / 3;
			n = (n % 3) + (n - (n % 3)) / 3;
		}
		ans += (n == 2) ? 1 : 0;
		cout << ans << "\n";
	}
	return 0;
}
