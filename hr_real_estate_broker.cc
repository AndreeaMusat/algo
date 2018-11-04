#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> clients_info;
vector<pair<int, int>> houses_info;
vector<bool> visited;
unordered_map<int, int> matches; // matches[client_idx] = house_idx

bool can_buy(int client_idx, int house_idx) {
  return (houses_info[house_idx].first > clients_info[client_idx].first) &&
         (houses_info[house_idx].second <= clients_info[client_idx].second);
}

bool bipartite_matching(int house_idx) {
  if (visited[house_idx])
    return false;

  visited[house_idx] = true;

  for (size_t client_idx = 0; client_idx < clients_info.size(); client_idx++) {
    if (can_buy(client_idx, house_idx)) {
      if ((matches.find(client_idx) == matches.end()) ||
          (bipartite_matching(matches[client_idx]))) {
        matches[client_idx] = house_idx;
        return true;
      }
    }
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);

  int n, m; // n clients, m houses
  cin >> n >> m;

  clients_info.resize(n);
  houses_info.resize(m);

  for (int i = 0; i < n; i++) {
    cin >> clients_info[i].first >> clients_info[i].second;
  }

  for (int i = 0; i < m; i++) {
    cin >> houses_info[i].first >> houses_info[i].second;
  }

  int sold_houses = 0;
  for (int i = 0; i < m; i++) {
    visited.assign(m, false);
    sold_houses += bipartite_matching(i);
  }

  cout << sold_houses << "\n";
}