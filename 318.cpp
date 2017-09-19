/*
	Author: Andreea Musat
	Date: 19 sept 2017

	Dijkstra + some magic trick
	Uva 318 - Domino Effect
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=254
*/

#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

int main()
{
	vector<vector<pair<int, int>>> graph;
	int n, m, u, v, w, left, right, cnt = 1;
	float max_dist = INT_MIN, meet_in_the_middle_dist;

	while (true)
	{
		max_dist = INT_MIN;

		cin >> n >> m;
		if (n == 0 && m == 0)
			break;

		if (graph.size() > 0)
			graph.clear();
		graph.resize(n, vector<pair<int, int>>());

		/* Read unidirected graph */
		for (int i = 0; i < m; i++)
		{
			cin >> u >> v >> w;
			graph[u - 1].push_back(make_pair(w, v - 1));
			graph[v - 1].push_back(make_pair(w, u - 1));
		}

		vector<int> dist(n, INF);
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		
		dist[0] = 0;
		pq.push(make_pair(0, 0)); 

		/* Dijkstra loop - at each step, take smallest distance and try to expand 
		   this path */
		while (!pq.empty())
		{
			pair<int, int> front = pq.top();
			pq.pop();

			int dis = front.first;
			int node = front.second;

			if (dis > dist[node])
				continue;

			for (auto neigh : graph[node])
			{
				if (dist[node] + neigh.first < dist[neigh.second])
				{
					dist[neigh.second] = dist[node] + neigh.first;
					pq.push(make_pair(dist[neigh.second], neigh.second));
				}
			}
		}

		/* Find maximum distance and the index of the node that has it */
		for (int i = 0; i < dist.size(); i++)
		{
			if (dist[i] > max_dist)
			{
				max_dist = dist[i];
				left = right = i;
			}
		}

		/* Now for every possible edge, check if it is possible for the domnioes
		   to meet in the middle. If so, compute meeting time and store it if it's
		   greater than current maximum meeting time */
		for (int i = 0; i < n; i++)
		{
			for (auto neigh : graph[i])
			{
				/* Check the pairs once */
				if (i < neigh.second)
				{
					u = dist[i], v = dist[neigh.second], w = neigh.first;
					if (u > v) swap(u, v);
					if (u + w > v)
					{
						meet_in_the_middle_dist = u + 1.0f * (w + v - u) / 2;
						if (meet_in_the_middle_dist > max_dist)
						{
							max_dist = meet_in_the_middle_dist;
							left = i, right = neigh.second;
						}
					}
				}
			}
		}

		cout << "System #" << cnt++ << "\n";
		cout << "The last domino falls after " << fixed << setprecision(1) << max_dist << " seconds, ";

		if (left == right)
			cout << "at key domino " << left + 1 << ".\n";
		else
			cout << "between key dominoes " << left + 1 << " and " << right + 1 << ".\n";

		cout << "\n";
	}
}
