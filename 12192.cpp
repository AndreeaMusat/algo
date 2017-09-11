/*
	Author: Andreea Musat
	Date: 11 sept 2017

	Find largest square sub-matrix that has all elements in given range; Compile using -std=c++11
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3344
*/

#include <bits/stdc++.h>
using namespace std;

int findLargestSubmatrixInRange(const vector<vector<int>>& matrix, int l, int h)
{
	int max_size = 0;
	int num_rows = int(matrix.size());
	int num_cols = int(matrix[0].size());

	for (int row = 0; row < num_rows; row++)
	{
		/* find position of first element in row that is greater or equal to l */
		vector<int>::const_iterator lower_bnd = lower_bound(matrix[row].begin(), matrix[row].end(), l);

		/* if no element was found, continue */
		if (lower_bnd == matrix[row].end())
			continue;

		/* otherwise find column index of this element */
		int col = lower_bnd - matrix[row].begin();

		/* find max size of square starting at (row, col) */
		int max_crt_size = min(num_rows - row, num_cols - col) - 1;

		/* we try every square, starting with the largest and update max size 
		   if current square has all elements in given range */
		for (int size = max_crt_size; size >= 0; size--)
		{
			if (matrix[row + size][col + size] <= h)
			{
				// cout << "max_size = " << size << "\n";
				max_size = max(max_size, size + 1);
				break;
			}
		}
	}

	return max_size;
}

int main()
{
	int n = 0, m = 0, q = 0;
	int low = 0, high = 0, result = 0;
	ios_base::sync_with_stdio(0);

	while (true)
	{
		cin >> n >> m;

		// check for invalid input
		if (n == 0 && m == 0)
			break;

		// read the matrix
		vector<vector<int>> matrix(n, vector<int>(m));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> matrix[i][j];

		cin >> q;
		for (int i = 0; i < q; i++)
		{
			cin >> low >> high;
			result = findLargestSubmatrixInRange(matrix, low, high);
			cout << result << "\n";
		}

		cout << "-\n";
	}
}
