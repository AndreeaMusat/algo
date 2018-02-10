#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T, line_idx;
	int N, M, i, j, k, l;
	int sum_mat[25][25];
	int curr_sum, curr_area;
	int max_area = 0;
	bool first = true;
	string mat[25];	
	string line;

	getline(cin, line);
	T = stoi(line, nullptr);
	getline(cin, line); // read empty line
	
	while (T--)
	{
		getline(cin, line);
		line_idx = 0, max_area = 0;
		
		while (line[0] == '0' or line[0] == '1')
		{
			mat[line_idx++] = line;
			getline(cin, line);
		}

		if (!first)
			cout << "\n";
		first = false;

		N = line_idx, M = (int)mat[0].size();
		for (i = 0; i < N; i++)
			for (j = 0; j < M; j++)
			{
				sum_mat[i][j] = int(mat[i][j] - '0');
				if (i > 0) sum_mat[i][j] += sum_mat[i - 1][j];
				if (j > 0) sum_mat[i][j] += sum_mat[i][j - 1];
				if (i > 0 and j > 0) sum_mat[i][j] -= sum_mat[i - 1][j - 1];
			}

		for (i = 0; i < N; i++)
			for (j = 0; j < M; j++)
				for (k = i; k < N; k++)
					for (l = j; l < M; l++)
					{
						curr_sum = sum_mat[k][l];
						if (i > 0) curr_sum -= sum_mat[i - 1][l];
						if (j > 0) curr_sum -= sum_mat[k][j - 1];
						if (i > 0 and j > 0) curr_sum += sum_mat[i - 1][j - 1];
						curr_area = (k - i + 1) * (l - j + 1);
						if (curr_area == curr_sum and curr_area > max_area)
							max_area = curr_area;
					}
		cout << max_area << "\n";
	}


}