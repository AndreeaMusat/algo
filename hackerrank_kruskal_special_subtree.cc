#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
  UnionFind(int n) {
    parent_.assign(n, 0);
    rank_.assign(n, 0);

    for (int i = 0; i < n; i++) {
      parent_[i] = i;
    }
  }

  int findSet(int i) {
    if (parent_[i] == i) {
      return i;
    }

    return parent_[i] = findSet(parent_[i]);
  }

  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  void unionSet(int i, int j) {
    if (!isSameSet(i, j)) {
      int pi = findSet(i);
      int pj = findSet(j);

      if (rank_[pi] > rank_[pj]) {
        parent_[pj] = pi;
      } else {
        parent_[pi] = pj;
        if (rank_[pi] == rank_[pj]) {
          rank_[pj]++;
        }
      }
    }
  }

private:
  vector<int> parent_;
  vector<int> rank_;
};

int main() {
  ios_base::sync_with_stdio(false);

  int V, E, u, v, w;
  vector<pair<int, pair<int, int>>> edges;

  cin >> V >> E;

  for (int i = 0; i < E; i++) {
    cin >> u >> v >> w;
    u--, v--;
    edges.push_back({w, {u, v}});
  }

  // nice lambda sorting
  sort(edges.begin(), edges.end(), [](const pair<int, pair<int, int>> &edge1,
                                      const pair<int, pair<int, int>> &edge2) {
    return (edge1.first < edge2.first)
               ? true
               : ((edge1.first == edge2.first)
                      ? ((edge1.first + edge1.second.first +
                          edge1.second.second) <
                         (edge2.first + edge2.second.first +
                          edge2.second.second))
                      : false);
  });

  UnionFind uf(V);

  int num_edges = 0;
  long long total_mst_weight = 0;
  for (int i = 0; i < E; i++) {
    pair<int, pair<int, int>> crt_edge = edges[i];
    if (!uf.isSameSet(crt_edge.second.first, crt_edge.second.second)) {
      total_mst_weight += crt_edge.first;
      num_edges += 1;
      uf.unionSet(crt_edge.second.first, crt_edge.second.second);
    }

    // MST is complete, no need to check other edges
    if (num_edges == V - 1) {
      break;
    }
  }

  cout << total_mst_weight << "\n";
}
