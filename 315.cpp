/*
	Author: Andreea Musat
	Date: 23 Sept 2017

	Find articulation points in graph
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=251
*/
#include <bits/stdc++.h>
using namespace std;
const int UNIVISITED = -1;
int dfsCnt, dfsRoot, rootChildren;
vector<int> dfs_num;
vector<int> dfs_low;
vector<int> dfs_parent;
vector<bool> articulation_vertex;

void findArticulationPoins(const vector<vector<int>>& graph, int u)
{
	/* dfs_low[u] = iteration counter when node u is visited for the first time 
	dfs_num[u] = lowest dfs_low[i] reachable from the current DFS spanning subtree of u */
	dfs_low[u] = dfs_num[u] = dfsCnt++;
	for (int neighbour : graph[u])
	{
		if (dfs_num[neighbour] == UNIVISITED)
		{
			dfs_parent[neighbour] = u;

			/* count children of dfs root (root is articulation point only if it has more 
			   than one child) */
			if (u == dfsRoot)
				rootChildren += 1;

			findArticulationPoins(graph, neighbour);

			/* dfs_low(v) is not smaller than dfs_num(u) implies that there is no back edge 
			from vertex v that can reach another vertex w with a lower dfs_num(w) than dfs_num(u). 
			A vertex w with lower dfs_num(w) than vertex u with dfs_num(u) implies that w is the 
			ancestor of u in the DFS spanning tree. This means that to reach the ancestor(s) of u 
			from v, one must pass through vertex u. Therefore, removing vertex u will disconnect the graph*/
			if (dfs_low[neighbour] >= dfs_num[u])
				articulation_vertex[u] = true;

			dfs_low[u] = min(dfs_low[u], dfs_low[neighbour]);
		}
		else if (neighbour != dfs_parent[u])
		{
			dfs_low[u] = min(dfs_low[u], dfs_num[neighbour]);
		}
	}
}

int main()
{
	int n, u, v;
	string line;
	vector<vector<int>> graph;
	
	while (true)
	{
		cin >> n;
		getline(cin, line);
		if (n == 0)
			break;

		graph.clear();
		graph.resize(n, vector<int>());

		while (true)
		{
			getline(cin, line);
			istringstream iss(line);
			iss >> u;
			if (u == 0)
				break;
			
			while (iss >> v)
			{
				graph[u - 1].push_back(v - 1);
				graph[v - 1].push_back(u - 1);
			}
		}

		dfsCnt = 0;
		dfs_num.assign(n, UNIVISITED);
		dfs_low.assign(n, 0);
		dfs_parent.assign(n, 0);
		articulation_vertex.assign(n, false);

		for (int i = 0; i < n; i++)
		{
			if (dfs_num[i] == UNIVISITED)
			{
				dfsRoot = i; rootChildren = 0;
				findArticulationPoins(graph, dfsRoot);
				articulation_vertex[dfsRoot] = (rootChildren > 1);
			}
		}
		
		int cntArticulationPoints = 0;
		for (int i = 0; i < n; i++)
		{
			if (articulation_vertex[i])
				cntArticulationPoints += 1;
		}

		cout << cntArticulationPoints << "\n";
	}
}
