/*
	Author: Andreea Musat
	Date : 29 sept 2017

	String matching in 2D grid
	https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2258
*/
#include <bits/stdc++.h>
using namespace std;

const int GRID_DIM = 4;
char grid[GRID_DIM][GRID_DIM];
vector<pair<int, int>> neighbours = 
	{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
	 {0, 1}, {1, -1}, {1, 0}, {1, 1}};



bool findAux(string word, int idx, int i, int j, vector<vector<int>>& visited)
{
	/* Matched until the end */
	if (idx >= (int)word.size())
		return true;

	/* Out of bounds */
	if (i < 0 || j < 0 || i >= GRID_DIM || j >= GRID_DIM)
		return false;

	/* Cell already visited */
	if (visited[i][j])
		return false;

	/* Mismatch at current char */
	if (word[idx] != grid[i][j])
		return false;

	/* Try to find the rest of the string - explore all the neighbours */
	visited[i][j] = 1;
	for (auto neigh : neighbours)
		if (findAux(word, idx + 1, i + neigh.first, j + neigh.second, visited))
			return true;
	
	/* Mark it as unvisited again - it was not used if we are here */
	visited[i][j] = 0;
	return false;
}

bool find(string word)
{
	vector<vector<int>> visited;

	/* Start the search from each cell of the grid */
	for (int i = 0; i < GRID_DIM; i++)
		for (int j = 0; j < GRID_DIM; j++)
		{
			visited.clear();
			visited.resize(GRID_DIM, vector<int>(GRID_DIM, 0));

			if (findAux(word, 0, i, j, visited))
				return true;
		}

	return false;
}

int main()
{
	int T, i, j, w, total, cnt = 1;
	string word;
	unordered_map<int, int> points = {{3, 1}, {4, 1}, {5, 2}, {6, 3}, {7, 5}};
	for (i = 8; i <= 16; i++)
		points[i] = 11;

	cin >> T;
	while (T--)
	{
		for (i = 0; i < GRID_DIM; i++)
			for (j = 0; j < GRID_DIM; j++)
				cin >> grid[i][j];

		total = 0;
		cin >> w;
		for (i = 0; i < w; i++)
		{
			cin >> word;
			if (find(word)) 
				total += points[(int)word.size()];
		}

		cout << "Score for Boggle game #" << cnt++ << ": " << total << "\n";
	}
}
