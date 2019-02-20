#include <bits/stdc++.h>
using namespace std;

int NaN = -1;
int memo[5001][5001];

int bkt(const string &s1, const string &s2, size_t i, size_t j) {
  if (memo[i][j] != NaN)
    return memo[i][j];
  if (i >= s1.size() or j >= s2.size())
    return 0;
  if (s1[i] == s2[j])
    return memo[i][j] = (1 + bkt(s1, s2, i + 1, j + 1));
  int ans1 = bkt(s1, s2, i + 1, j);
  int ans2 = bkt(s1, s2, i, j + 1);
  return memo[i][j] = ((ans1 >= ans2) ? ans1 : ans2);
}

int bkt(const string &s1, const string &s2) { return bkt(s1, s2, 0, 0); }

int main() {
  string s1, s2;
  memset(memo, -1, sizeof(memo));
  cin >> s1 >> s2;
  cout << bkt(s1, s2) << "\n";
}