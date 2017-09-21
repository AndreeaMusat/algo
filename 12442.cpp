/*
	Author: Andreea Musat
	Date: 20 sept 2017

	Find starting point of largest path in a particular graph (every node has a single neighbour)

	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3873
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

ostream& operator<<(ostream& os, vector<int> v)
{
	for (size_t i = 0; i < v.size(); i++)
		os << v[i] << " ";
	os << "\n";
	return os;
}

int dfs(const vector<int>& graph, vector<int>& dist, vector<bool>& visited, int s)
{
	visited[s] = true;

	int neighbour = graph[s], len = 0;
	if (!visited[neighbour])
		len = 1 + dfs(graph, dist, visited, neighbour);

	visited[s] = false;

	return dist[s] = len;
}


int main()
{
	int T, n, i, u, v, cnt = 1;
	vector<int> graph;
	vector<int> dist;
	vector<bool> visited;

	cin >> T;
	
	while (T--)
	{
		cin >> n;

		graph.clear(); dist.clear(); visited.clear();
		graph.resize(n); dist.resize(n, INF); visited.resize(n, false);

		for (i = 0; i < n; i++)
		{
			cin >> u >> v;
			graph[u - 1] = v - 1;
		}

		
		dist.resize(n, INF);

		int max_res = INT_MIN, crt_res;
		int starting_point = -1;

		for (i = 0; i < n; i++)
		{
			if (dist[i] == INF)
			{
				crt_res = dfs(graph, dist, visited, i);

				if (crt_res > max_res)
				{
					max_res = crt_res;
					starting_point = i;
				}
			}
		}

		cout << "Case " << cnt++ << ": " << starting_point + 1 << "\n";
	}

	return 0;
}
