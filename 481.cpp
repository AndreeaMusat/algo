/*
	Author: Andreea Musat
	Date: 14 Sept 2017

	O(n log k) LIS (where k = length of lis) from CP3

	https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=422
*/

#include <bits/stdc++.h>
using namespace std;

// print reversed vector
ostream& operator<<(ostream& os, const vector<int>& v)
{
	for (int i = (int)v.size() - 1; i >= 0; i--)
	{
		os << v[i] << "\n";
	}
}

int main()
{
	int x, n, crt, pos;
	int lis_len = 0, lis_end = 0;
	vector<int> arr, lis_path;
	
	while (cin >> x)
	{
		arr.push_back(x);
	}

	n = (int)arr.size();
	int L[n], L_id[n], P[n];

	for (int i = 0; i < n; i++)
	{
		pos = lower_bound(L, L + lis_len, arr[i]) - L; // pos = length of LIS whose last element can be current element
		L[pos] = arr[i]; // arr[i] is now the last element from LIS with pos + 1 elements
		L_id[pos] = i;   // index of element used as last element for LIS with pos + 1 elements
		P[i] = pos ? L_id[pos - 1] : -1;  // parent of current element (index of last element of previous sequence)
		
		if (pos + 1 >= lis_len)
		{
			lis_len = pos + 1;
			lis_end = i;
		}
	}

	// reconstruct path by going from last element to its parent
	crt = lis_end;
	while (P[crt] >= 0)
	{
		lis_path.push_back(arr[crt]);
		crt = P[crt];
	}
	lis_path.push_back(arr[crt]);

	cout << lis_len << "\n-\n";
	cout << lis_path;
	return 0;
}
