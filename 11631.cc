#include <bits/stdc++.h>
using namespace std;

struct Edge
{
	Edge() {}
	Edge(int x, int y, int cost): x_(x), y_(y), cost_(cost) {}
	
	int x_, y_, cost_;
};

struct UnionFind
{
	UnionFind() {}
	UnionFind(int V): V_(V), parents_(V), ranks_(V, 0) {
		for (int i = 0; i < V; i++) parents_[i] = i;
	}

	int findSet(int x)
	{
		return parents_[x] == x ? x : findSet(parents_[x]);
	}

	bool isSameSet(int x, int y)
	{
		return findSet(x) == findSet(y);
	}

	void Union(int x, int y)
	{
		if (!isSameSet(x, y))
		{
			int xp = findSet(x);
			int yp = findSet(y);

			if (ranks_[xp] > ranks_[yp])
			{
				parents_[yp] = xp;
			}
			else 
			{
				parents_[xp] = yp;
				if (ranks_[xp] == ranks_[yp]) ++ranks_[yp];
			}
		}
	}

	int V_;
	vector<int> parents_;
	vector<int> ranks_;
};

int kruskal(int n, vector<Edge>& edges)
{
	int mst_cost = 0;
	UnionFind uf(n);

	sort(edges.begin(), edges.end(), [] (const Edge& e1, const Edge& e2) { 
		return e1.cost_ < e2.cost_; });

	for (const auto& edge : edges)
	{
		if (!uf.isSameSet(edge.x_, edge.y_))
		{
			uf.Union(edge.x_, edge.y_);
			mst_cost += edge.cost_;
		}
	}

	return mst_cost;
}

int main() 
{
	int n, m, u, v, c;

	while (true)
	{
		cin >> n >> m;
		if (n == 0 && m == 0) break;

		long total_cost = 0;
		vector<Edge> edges;

		for (int i = 0; i < m; i++)
		{
			cin >> u >> v >> c;
			edges.emplace_back(u, v, c);
			total_cost += c;
		}

		cout << total_cost - kruskal(n, edges) << "\n";
	}
}