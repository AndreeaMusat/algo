#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m, alice, geq_alice;
  vector<int> scores;
  vector<int> cnt_uniques_right;
  cin >> n;
  scores.assign(n, 0);
  cnt_uniques_right.assign(n, 1);

  for (int i = 0; i < n; i++) {
    cin >> scores[i];
  }

  sort(scores.begin(), scores.end());
  for (int i = n - 2; i >= 0; i--) {
    cnt_uniques_right[i] =
        cnt_uniques_right[i + 1] + (scores[i] != scores[i + 1]);
  }

  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> alice;
    geq_alice =
        lower_bound(scores.begin(), scores.end(), alice) - scores.begin();
    if (geq_alice >= n) {
      cout << 1 << "\n";
    }
    else if (scores[geq_alice] != alice) {
      cout << cnt_uniques_right[geq_alice] + 1 << "\n";
    }
    else {
      cout << cnt_uniques_right[geq_alice] << "\n";
    }
  }
}