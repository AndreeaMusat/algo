/*
	Author: Andreea Musat
  Date: 28 sept 2017
  
	String Matching in 2D Grid
  https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=951
*/

#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
pair<int, int> ans;
string word;
vector<int> di = {-1, -1, -1, 0, 0, 1, 1, 1};
vector<int> dj = {-1, 0, 1, -1, 1, -1, 0, 1};
const int num_neighbours = 8;

bool find(int i, int j, int idx, int dir)
{
	/* Matched until the end of the word, return true */
	if (idx >= word.size())
		return true;

	/* Indices outside the grid */
	if (i < 0 || j < 0 ||
		i >= grid.size() || 
		j >= grid[0].size())
		return false;
	
	/* Mismatch at current char */
	if (tolower(int(grid[i][j])) != tolower(int(word[idx])))
		return false;

	/* Direction already established, should only check that */
	if (dir != -1)
	{
		bool res = find(i + di[dir], j + dj[dir], idx + 1, dir);
		if (res)
			return true;
	}
	/* Direction of search not established yet, so we should try
	   all the possible directions */
	else
	{
		bool res;
		for (int ii = 0; ii < num_neighbours; ii++)
		{
			res = find(i + di[ii], j + dj[ii], idx + 1, ii);
			if (res)
				return true;
		}
	}

	return false;
}

int main()
{
	int T, n, m, i, q;

	cin >> T;

	while (T--)
	{
		cin >> n >> m;
		grid.clear();
		grid.resize(n);
		
		for (i = 0; i < n; i++)
			cin >> grid[i];

		cin >> q;
		for (int qq = 0; qq < q; qq++)
		{
			cin >> word;
			
			bool found = false;
			
			/* We are looking for the uppermost leftmost match of the 
			   word in the grid, so we should check the rows from left to right, 
			   starting with row 0 */
			for (int i = 0; i < n && !found; i++)
			{
				for (int j = 0; j < m && !found; j++)
				{	
					bool res = find(i, j, 0, -1);
					if (res)
					{
						cout << i + 1 << " " << j + 1 << "\n";
						found = true;
					}
				}
			}
		}
		if (T) cout << "\n";
	}
}
