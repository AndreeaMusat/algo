/*
	Author: Andreea Musat
	Date: 19 sept 2017

	Uva 103 - Ancient Messages
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3544
*/

#include <bits/stdc++.h>
using namespace std;

const int DIM = 256;
const int INF = 0x3f3f3f3f;
const int NUM_NEIGH = 4;

int h, w;
int image[DIM][DIM];
pair<int, int> neighbours[] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

/* Check if cell is outside the image */
bool outOfBounds(int i, int j)
{
	return (i < 0 || j < 0 || i >= h || j >= 4 * w);
}

/* 
Explore cells of a hyeroglyph: 
	- go from black pixels to other black pixels 
	- go from black pixels to withe pixels (and increase no of connected comps
	- go from white pixels to other white pixels 
*/
int dfs(int i, int j, int crt_color, int paint_color)
{
	int connected_comp_no = 0;

	image[i][j] = paint_color;
	for (int n = 0; n < NUM_NEIGH; n++)
	{
		/* Get indices of current neighbour pixel */
		int newi = i + neighbours[n].first;
		int newj = j + neighbours[n].second;

		if (!outOfBounds(newi, newj))
		{
			/* Black -> Black (+ add no of connected comps found when exploring this neighbor) */
			if (crt_color == -1 && image[newi][newj] == -1)
			{
				connected_comp_no += dfs(newi, newj, crt_color, paint_color);
			}

			/* White -> white */
			else if (crt_color == 0 && image[newi][newj] == 0)
			{
				dfs(newi, newj, crt_color, paint_color);
			}

			/* Black -> white (+ increase no of connected components */
			else if (crt_color == -1 && image[newi][newj] == 0)
			{
				dfs(newi, newj, 0, ++connected_comp_no);
			}
		}
	}

	return connected_comp_no;
}

/* Floodfill for (white) background - similar to the one above; made a 
   different function for readability */
void dfs_background(int i, int j, int crt_color, int paint_color)
{
	if (image[i][j] != crt_color)
		return;

	image[i][j] = paint_color;
	for (int n = 0; n < NUM_NEIGH; n++)
	{
		int newi = i + neighbours[n].first;
		int newj = j + neighbours[n].second;
		
		if (!outOfBounds(newi, newj))
		{
			dfs_background(newi, newj, crt_color, paint_color);
		}
	}
}

int main()
{
	int i, j, cnt = 1;

	/* Map the number of connected components to the corresponding hyeroglyph */
	unordered_map<int, char> mp;
	mp[0] = 'W'; mp[1] = 'A'; mp[2] = 'K'; mp[3] = 'J'; mp[4] = 'S'; mp[5] = 'D'; 

	while (true)
	{
		cin >> h >> w;

		if (h == 0 && w == 0)
			break;

		memset(image, 0, sizeof image);

		/* Read input image (in hex) and store white pixels using 0 and black
		   pixels using -1 */
		for (i = 0; i < h; i++)
		{
			string line;
			cin >> line;
			for (j = 0; j < (int)line.size(); j++)
			{
				int crt_num = (line[j] >= 'a' && line[j] <= 'f') ? 
							   line[j] - 'a' + 10 : 
							   line[j] - '0';

				int cnt = 3;
				while (crt_num)
				{
					image[i][j * 4 + cnt--] = (crt_num & 1) ? -1 : 0;
					crt_num >>= 1;
				}
			}
		}

		/* Set value of white background pixels to INF to mark them as explored */
		for (j = 0; j < 4 * w; j++)
		{
			dfs_background(0, j, 0, INF);
			dfs_background(h - 1, j, 0, INF);
		}

		for (i = 0; i < h; i++)
		{
			dfs_background(i, 0, 0, INF);
			dfs_background(i, 4 * w - 1, 0, INF);
		}

		/* result[i] = no of hyeroglyphs found with i connected components */
		int result[6] = {0, 0, 0, 0, 0, 0};
		for (i = 0; i < h; i++)
		{
			for (j = 0; j < 4 * w; j++)
			{
				if (image[i][j] == -1)
				{
					int cnt_connected_comp = dfs(i, j, -1, -INF);
					result[cnt_connected_comp] += 1;
				}
			}
		}

		/* Form result and sort it */
		string res;
		for (int i = 0; i < 6; i++)
		{
			res += string(result[i], mp[i]);
		}

		sort(res.begin(), res.end());
		cout << "Case " << cnt++ << ": " << res << "\n";	
	}
}
