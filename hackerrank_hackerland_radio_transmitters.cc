#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);

  int n, k, crt = 0, max_num, ans = 1;

  cin >> n >> k;
  vector<int> x(n, 0);

  for (int i = 0; i < n; i++) {
    cin >> x[i];
  }

  sort(x.begin(), x.end());

  while (true) {
    max_num = x[crt] + k;
    while (x[crt] <= max_num && crt < n)
      crt += 1;
    crt -= 1; // now crt is the first not greater than max_num
    max_num = x[crt] + k;
    while (x[crt] <= max_num && crt < n)
      crt += 1;
  }
}