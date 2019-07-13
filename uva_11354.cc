// Saturday evening fun.

#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int u, v, d;
  Edge(int u, int v, int d) : u(u), v(v), d(d) {}
  bool operator<(const Edge &other) { return d < other.d; }
};

vector<vector<pair<int, int>>> get_mst(const vector<Edge> &edges, int n,
                                       int m) {
  vector<Edge> ans;
  vector<int> parents(n);

  iota(parents.begin(), parents.end(), 0);

  function<int(int)> find = [&](int x) -> int {
    if (parents[x] != x) {
      parents[x] = find(parents[x]);
    }
    return parents[x];
  };

  for (int i = 0; i < m; i++) {
    int u_comp = find(edges[i].u);
    int v_comp = find(edges[i].v);

    if (u_comp != v_comp) {
      parents[u_comp] = parents[v_comp];
      ans.push_back(edges[i]);
    }

    if (ans.size() == n - 1)
      break;
  }

  vector<vector<pair<int, int>>> graph(n);
  for (int i = 0; i < int(ans.size()); i++) {
    graph[ans[i].u].push_back({ans[i].v, ans[i].d});
    graph[ans[i].v].push_back({ans[i].u, ans[i].d});
  }

  return graph;
}

void dfs(const vector<vector<pair<int, int>>> &mst, vector<vector<int>> &up,
         vector<vector<int>> &mx, vector<int> &depth, int node, int parent,
         int weight, int crt_depth = 0) {
  up[node][0] = parent;
  mx[node][0] = weight;
  depth[node] = crt_depth;

  // fckin hell.
  for (int i = 1; i < up[0].size(); i++) {
    up[node][i] = up[up[node][i - 1]][i - 1];
    mx[node][i] = max(mx[node][i - 1], mx[up[node][i - 1]][i - 1]);
  }

  for (const auto &neigh : mst[node]) {
    if (neigh.first != parent) {
      dfs(mst, up, mx, depth, neigh.first, node, neigh.second, crt_depth + 1);
    }
  }
}

int query(const vector<vector<int>> &up, const vector<vector<int>> &mx,
          const vector<int> &depth, int x, int y) {
  if (depth[x] < depth[y]) {
    swap(x, y);
  }

  // x is deeper.
  int max_ans = INT_MIN;
  int diff = depth[x] - depth[y];
  for (int i = 0; i < 8 * sizeof(diff); i++) {
    if (diff & (1 << i)) {
      max_ans = max(max_ans, mx[x][i]);
      x = up[x][i];
    }
  }

  if (x == y) {
    return max_ans;
  }

  for (int i = int(up[0].size()) - 1; i >= 0; i--) {
  	// this is lca or higher.
    if (up[x][i] == up[y][i]) {
      continue;
    }
    max_ans = max({max_ans, mx[x][i], mx[y][i]});
    x = up[x][i];
    y = up[y][i];
  }

  return max({max_ans, mx[x][0], mx[y][0]});
}

int main() {
  int n, m, q, s, t, x, y, d, cnt_test = 0;
  ios_base::sync_with_stdio(false);

  while (cin >> n >> m) {
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
      cin >> x >> y >> d;
      edges.emplace_back(Edge(x - 1, y - 1, d));
    }
    cin >> q;

    sort(edges.begin(), edges.end());
    auto mst = get_mst(edges, n, m);

    // up[n][i] = the 2^ith ancestor of n.
    vector<vector<int>> up(n, vector<int>(ceil(log2(n + 1)), 0));
    vector<vector<int>> mx(n, vector<int>(ceil(log2(n + 1)), 0));
    vector<int> depth(n, 0);

    dfs(mst, up, mx, depth, 0, 0, 0);

    if (cnt_test)
      cout << "\n";
    for (int i = 0; i < q; i++) {
      cin >> s >> t;
      --s, --t;
      cout << query(up, mx, depth, s, t) << "\n";
    }
    ++cnt_test;
  }
}
