/*
	Author: Andreea Musat
	Date: 23 Sept 2017

	Count number of vertices in each set of bipartite graph
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1446
*/

#include <bits/stdc++.h>
using namespace std;

const int UNVISITED = 0;
const int MONTESCO = 1;
const int CAPULETO = -1;
const int MAXN = 200;

int count_montesco;

int bfs(const vector<vector<int>>& graph, vector<int>& family, int node, int fam)
{
	family[node] = fam;
	bool bipartite_graph = true;
	int count_montesco = (fam == MONTESCO) ? 1 : 0;
	int count_capuleto = (fam == CAPULETO) ? 1 : 0;
	queue<int> node_queue;
	node_queue.push(node);
	
	while (!node_queue.empty())
	{
		int front_node = node_queue.front();
		node_queue.pop();

		for (int neighbour : graph[front_node])
		{
			if (family[neighbour] == UNVISITED)
			{
				family[neighbour] = -family[front_node];
				count_montesco += (family[neighbour] == MONTESCO) ? 1 : 0;
				count_capuleto += (family[neighbour] == CAPULETO) ? 1 : 0;
				node_queue.push(neighbour);
			}
			else if (family[neighbour] == family[front_node])
			{
				/* if the graph is not bipartite, then no one from this connected 
				   component will be invited, so we set this variable to false, but
				   continue running BFS to know we already checked this component */
				bipartite_graph = false;
			}
		}
	}

	if (bipartite_graph)
		return max(count_capuleto, count_montesco);
	return 0;
}

int main()
{
	int M, N, no_enemies;
	int enemy;
	vector<vector<int>> graph;
	vector<int> family;
	cin >> M;
	while (M--)
	{
		cin >> N;

		graph.clear(); graph.resize(MAXN);
		family.clear(); family.resize(MAXN, UNVISITED); 
		for (int i = 0; i < N; i++)
		{
			cin >> no_enemies;
			for (int j = 0; j < no_enemies; j++)
			{
				cin >> enemy;

				/* unexpected test case: enemy having a number greater than
				   N should be ignored (not mentioned anywhere..) thanks udebug */
				if (enemy > N)
					continue;
				graph[i].push_back(enemy - 1);
				graph[enemy - 1].push_back(i);
			}
		}

		int result = 0;
		for (int i = 0; i < N; i++)
		{
			if (family[i] == UNVISITED)
			{
				result += bfs(graph, family, i, MONTESCO);
			}
		}

		cout << result << "\n";
	}
}
