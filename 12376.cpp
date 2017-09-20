/*
 	Author: Andreea Musat
	Date: 20 sept 2017
	
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3798
*/

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, vector<int> v)
{
	for (size_t i = 0; i < v.size(); i++)
		os << v[i] << " ";
	os << "\n";
	return os;
}

int main()
{
	int T, n, m, u, v, test_no = 1;
	vector<int> cost;
	vector<vector<int>> graph;

	cin >> T;
	while (T--)
	{
		cin >> n >> m;

		if (cost.size() > 0)
			cost.clear();
		cost.resize(n);
		if (graph.size() > 0)
			graph.clear();
		graph.resize(n, vector<int>());

		for (int i = 0; i < n; i++)
			cin >> cost[i];

		for (int i = 0; i < m; i++)
		{
			cin >> u >> v;
			graph[u].push_back(v);
		}

		/* Greedily select node with highest cost at each step */
		int crt_node = 0;
		int total_cost_sum = 0;
		int max_cost_val = INT_MIN;
		int max_cost_idx = -1;

		while (true)
		{
			max_cost_val = INT_MIN;
			max_cost_idx = -1;

			for (auto neighbour : graph[crt_node])
			{
				if (cost[neighbour] > max_cost_val)
				{
					max_cost_val = cost[neighbour];
					max_cost_idx = neighbour;
				}
			}

			if (max_cost_val == INT_MIN)
				break;

			crt_node = max_cost_idx;
			total_cost_sum += max_cost_val;
		}

		cout << "Case " << test_no++ << ": " << total_cost_sum << " " << crt_node << "\n";
	}
}
