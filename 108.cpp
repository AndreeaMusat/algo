/*
	Author: Andreea Musat
	10 Feb 2018
*/	

#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, i, j, k, l;
	int arr[100][100];
	long max_subrect, tmp;

	cin >> N;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			cin >> arr[i][j];
			if (i > 0) arr[i][j] += arr[i - 1][j];
			if (j > 0) arr[i][j] += arr[i][j - 1];
			if (i > 0 and j > 0) arr[i][j] -= arr[i - 1][j - 1];
		}
	}

	max_subrect = LONG_MIN;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = i; k < N; k++)
				for (l = j; l < N; l++)
				{
					tmp = arr[k][l];
					if (i > 0) tmp -= arr[i - 1][l];
					if (j > 0) tmp -= arr[k][j - 1];
					if (i > 0 and j > 0) tmp += arr[i - 1][j - 1];
					if (tmp > max_subrect)
					{
						max_subrect = tmp;
					}
				}

	cout << max_subrect << "\n";
	return 0;
}