#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int source, const vector<vector<pair<int, int>>>& graph)
{
	vector<int> dist(graph.size(), INT_MAX);
	priority_queue<pair<int, int>, 
				   vector<pair<int, int>>, 
				   greater<pair<int, int>>> pq;

	dist[source] = 0; pq.push({0, source});
	while (!pq.empty())
	{
		auto front = pq.top(); pq.pop();
		int d = front.first, u = front.second;
		if (d > dist[u]) continue;
		for (const auto& neigh : graph[u])
		{
			int v = neigh.first;
			int cost = neigh.second;
			if (dist[u] + cost < dist[v])
			{
				dist[v] = dist[u] + cost;
				pq.push({dist[v], v});
			}
		}
	}

	return dist;
}

int main()
{
	int q, V, exit, time, E, u, v, cost, res;
	bool first = true;

	cin >> q;
	while (q--)
	{
		cin >> V >> exit >> time >> E;

		res = 0;
		vector<vector<pair<int, int>>> graph(V);

		for (int i = 0; i < E; i++)
		{
			cin >> u >> v >> cost;
			u--, v--;
			graph[v].push_back({u, cost});
		}

		auto dist = dijkstra(exit - 1, graph);
		
		for (const auto& d : dist)
		{
			if (d <= time) ++res;
		}

		if (!first) cout << "\n";
		else first = false;
		
		cout << res << "\n";

	}
}