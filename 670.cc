// UVA 670 
// Andreea Musat, Nov 2018

#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> bob_route;
vector<pair<int, int>> ralph_places;
// match[bob_index] = ralph_index
vector<int> match;
vector<int> visited;

double euclidean_distance(const pair<int, int> &p1, const pair<int, int> &p2) {
  return sqrt((p1.first - p2.first) * (p1.first - p2.first) +
              (p1.second - p2.second) * (p1.second - p2.second));
}

bool is_acessible(int ralph_idx, int bob_idx) {
  double bob_dist =
      euclidean_distance(bob_route[bob_idx], bob_route[bob_idx + 1]);
  double ralph_dist =
      euclidean_distance(bob_route[bob_idx], ralph_places[ralph_idx]) +
      euclidean_distance(ralph_places[ralph_idx], bob_route[bob_idx + 1]);
  return ralph_dist <= 2 * bob_dist;
}

bool bipartite_matching(int ralph_idx) {
  if (visited[ralph_idx]) {
    return false;
  }

  visited[ralph_idx] = true;
  for (int bob_idx = 0; bob_idx < (int)bob_route.size() - 1; bob_idx++) {
    if (is_acessible(ralph_idx, bob_idx)) {
      if (match[bob_idx] == -1 || bipartite_matching(match[bob_idx])) {
        match[bob_idx] = ralph_idx;
        return true;
      }
    }
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  vector<pair<int, int>> ralph_route;
  int L, N, M;
  cin >> L;
  for (int k = 0; k < L; k++) {

    cin >> N >> M;

    bob_route.resize(N);
    ralph_places.resize(M);
    match.assign(N, -1);
    ralph_route.clear();

    for (int i = 0; i < N; i++) {
      cin >> bob_route[i].first >> bob_route[i].second;
    }

    for (int i = 0; i < M; i++) {
      cin >> ralph_places[i].first >> ralph_places[i].second;
    }

    int visited_interesting_places = N;
    for (int ralph_idx = 0; ralph_idx < M; ralph_idx++) {
      visited.assign(M, false);
      visited_interesting_places += bipartite_matching(ralph_idx);
    }

    for (int i = 0; i < N; i++) {
      ralph_route.push_back(bob_route[i]);
      if (match[i] != -1) {
        ralph_route.push_back(ralph_places[match[i]]);
      }
    }

    cout << visited_interesting_places << "\n";
    for (int i = 0; i < (int)ralph_route.size(); i++) {
      cout << ralph_route[i].first << " " << ralph_route[i].second;
      if (i != (int)ralph_route.size() - 1)
        cout << " ";
    }

    if (k != L - 1) {
      cout << "\n\n";
    } else {
      cout << "\n";
    }
  }
}
