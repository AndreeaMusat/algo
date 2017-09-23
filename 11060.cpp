/*
	Author: Andreea Musat
	Date: 23 Sept 2017

	Toposort (using Khan's algorithm)
	https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2001
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, m, top_elem, cnt = 1;
	string before, after;
	vector<string> drink;
	vector<string> toposort_result;
	vector<int> in_degree;
	unordered_map<string, int> map_drinks;
	vector<vector<int>> graph;

	while (cin >> n)
	{
		drink.clear(); drink.resize(n);
		graph.clear(); graph.resize(n);
		in_degree.clear(); in_degree.resize(n, 0);
		toposort_result.clear(); 

		for (int i = 0; i < n; i++)
		{
			cin >> drink[i];
			map_drinks[drink[i]] = i;
		}
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			cin >> before >> after;
			graph[map_drinks[before]].push_back(map_drinks[after]);
			in_degree[map_drinks[after]] += 1;
		}

		priority_queue<int, vector<int>, greater<int>> khan_queue;
		for (int i = 0; i < n; i++)
		{
			if (in_degree[i] == 0)
			{
				khan_queue.push(i);
			}
		}		

		while (!khan_queue.empty())
		{
			top_elem = khan_queue.top();
			khan_queue.pop();
			toposort_result.push_back(drink[top_elem]);
			for (int neighbor : graph[top_elem])
			{
				if (--in_degree[neighbor] == 0)
				{
					khan_queue.push(neighbor);
				}
			}	
		}

		cout << "Case #" << cnt++ << ": Dilbert should drink beverages in this order: ";
		for (size_t i = 0; i < n; i++)
		{
			if (i != n - 1)
				cout << toposort_result[i] << " ";
			else
				cout << toposort_result[i] << ".\n\n";
		}
	}

}
