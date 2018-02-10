#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T, A, B, C;
	int i, j, k, l, m, n;
	long long arr[20][20][20];
	long long curr_sum = 0;
	long long max_sum = 0;
	bool first = true;
	
	cin >> T;

	while (T--)
	{
		if (!first) cout << "\n";
		first = false;

		cin >> A >> B >> C;
		for (i = 0; i < A; i++)
			for (j = 0; j < B; j++)
				for (k = 0; k < C; k++)
				{
					cin >> arr[i][j][k];
					if (i > 0) arr[i][j][k] += arr[i - 1][j][k];
					if (j > 0) arr[i][j][k] += arr[i][j - 1][k];
					if (k > 0) arr[i][j][k] += arr[i][j][k - 1];
					if (i > 0 and j > 0) arr[i][j][k] -= arr[i - 1][j - 1][k];
					if (i > 0 and k > 0) arr[i][j][k] -= arr[i - 1][j][k - 1];
					if (j > 0 and k > 0) arr[i][j][k] -= arr[i][j - 1][k - 1];
					if (i > 0 and j > 0 and k > 0) arr[i][j][k] += arr[i - 1][j - 1][k - 1];
				}

		max_sum = LLONG_MIN;
		for (i = 0; i < A; i++)
			for (j = 0; j < B; j++)
				for (k = 0; k < C; k++)
					for (l = i; l < A; l++)
						for (m = j; m < B; m++)
							for (n = k; n < C; n++)
							{
								curr_sum = arr[l][m][n];
								if (i > 0) curr_sum -= arr[i - 1][m][n];
								if (j > 0) curr_sum -= arr[l][j - 1][n];
								if (k > 0) curr_sum -= arr[l][m][k - 1];
								if (i > 0 and j > 0) curr_sum += arr[i - 1][j - 1][n];
								if (i > 0 and k > 0) curr_sum += arr[i - 1][m][k - 1];
								if (j > 0 and k > 0) curr_sum += arr[l][j - 1][k - 1];
								if (i > 0 and j > 0 and k > 0) curr_sum -= arr[i - 1][j - 1][k - 1];
								if (curr_sum > max_sum)
									max_sum = curr_sum;
							}

		cout << max_sum << "\n";
	}
}