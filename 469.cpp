/*
	Author: Andreea Musat
	Date: 17 sept 2017

	Find sizes of connected components in graph given as matrix
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=410
*/

#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> neighbours_delta = 
		{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
		 {0, 1}, {1, -1}, {1, 0}, {1, 1}};

pair<int, int> operator+(const pair<int, int>& p1, const pair<int, int>& p2)
{
	pair<int, int> result;
	result.first = p1.first + p2.first;
	result.second = p1.second + p2.second;
	return result;
}

ostream& operator<<(ostream& os, vector<int> v)
{
	for (size_t i = 0; i < v.size(); i++)
		os << v[i] << " ";
	os << "\n";
	return os;
}

bool isOutOfBounds(const vector<string>& grid, pair<int, int> point)
{
	/* Check if a cell is outside the grid */
	if (point.first < 0 || point.second < 0 ||
		point.first >= (int)grid.size() || point.second >= (int)grid[0].size())
	{
		return true;
	}
		
	return false;
}

void floodFill(vector<string>& grid, vector<vector<int>>& lakes_index, 
	vector<int>& lakes_size, int cnt_lakes, pair<int, int> start)
{
	/* Mark current cell as visited */
	grid[start.first][start.second] = 'V';

	/* Store connected component index for current cell */
	lakes_index[start.first][start.second] = cnt_lakes;

	/* Increase the size of current connected component */
	lakes_size[cnt_lakes] += 1;

	/* DFS: Visit every non-visited water cell that is a neighbour 
	   (diagonals included) of current cell */
	for (auto delta : neighbours_delta)
	{
		pair<int, int> neighbour = delta + start;
		if (!isOutOfBounds(grid, neighbour) &&
			grid[neighbour.first][neighbour.second] == 'W')
		{
			floodFill(grid, lakes_index, lakes_size, cnt_lakes, neighbour);
		}
	}
}

int main()
{
	int T, x, y, no_test = 0;
	string line, empty_line;
	vector<string> grid;
	vector<pair<int, int>> queries;

	getline(cin, line);
	T = stoi(line);

	while (T--)
	{
		/* Read empty line between testcases */
		getline(cin, empty_line);

		while (true)
		{
			/* If current line is not a grid line, then break 
			   (and read the queries) */
			if ((char)cin.peek() != 'L' &&
				(char)cin.peek() != 'W')
			{
				break;
			}

			getline(cin, line);
			grid.push_back(line);
		}

		int n = grid.size();
		int m = grid[0].size();

		/* Matrix having the same size as the initial grid: 
		   -1 for land cells, no of its connected component for
		   the water cells */
		vector<vector<int>> lakes_index(n, vector<int>(m, -1));

		/* Store size of every connected component */
		vector<int> lakes_size;

		/* Count number of connected component */
		int cnt_lakes = 0;

		/* Start a DFS from every Water cell that is not visited yet*/
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (grid[i][j] == 'W')
				{
					lakes_size.push_back(0);
					floodFill(grid, lakes_index, lakes_size, cnt_lakes, make_pair(i, j));
					cnt_lakes += 1;
				}
			}
		}

		/* Print newline between queries of different testcases */
		if (no_test != 0)
			cout << "\n";
		no_test += 1;

		/* Read queries and answer them */
		while (true)
		{
			if (!isdigit(cin.peek()))
				break;

			getline(cin, line);
			istringstream is(line);
			is >> x >> y;
			cout << lakes_size[lakes_index[x - 1][y - 1]] << "\n";
		}

		grid.clear();
	}
}
