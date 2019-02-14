#include <bits/stdc++.h>
using namespace std;

const int kLenAlpha = 26;
const long long kModulo = (long long)1e9 + 7;

// len(str) >= 1
// frequencies[i][j] = freq of char 'a' + j in str[0:i]
void precompute_frequencies(const string &str,
                            vector<vector<int>> &frequencies) {
  frequencies.assign(str.length(), vector<int>(kLenAlpha, 0));
  frequencies[0][str[0] - 'a'] = 1;

  for (int i = 1; i < (int)str.length(); i++) {
    for (char chr = 'a'; chr <= 'z'; chr++) {
      frequencies[i][chr - 'a'] =
          frequencies[i - 1][chr - 'a'] + (chr == str[i]);
    }
  }
}

void precompute_factorials(int n, vector<long long> &factorials) {
  factorials.assign(n + 1, 1);
  for (int i = 1; i <= n; i++) {
    factorials[i] = (factorials[i - 1] * i) % kModulo;
  }
}

long long mod_pow(long long base, long long pow) {
  long long ans = 1;
  long long exp = base;

  for (; pow > 0; pow >>= 1) {
    if (pow & 1) {
      ans = (ans * exp) % kModulo;
    }

    exp = (exp * exp) % kModulo;
  }

  return ans;
}

long long solve(const string &str, const vector<vector<int>> &frequencies,
                const vector<long long> &factorials, int low, int high) {
  int count_even_pairs = 0;
  int count_odd_uniques = 0;
  long long ans = 1;

  for (char chr = 'a'; chr <= 'z'; chr++) {
    int crt_freq = frequencies[high][chr - 'a'] -
                   (low > 0 ? frequencies[low - 1][chr - 'a'] : 0);
    count_even_pairs += crt_freq >> 1;
    count_odd_uniques += crt_freq % 2;
    ans = (ans * mod_pow(factorials[crt_freq >> 1], kModulo - 2));
  }

  ans = (ans * factorials[count_even_pairs]) % kModulo;
  if (count_odd_uniques > 0) {
    ans = (ans * count_odd_uniques) % kModulo;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);

  int low, high, q;
  string str;
  vector<long long> factorials;
  vector<vector<int>> frequencies;

  cin >> str >> q;

  precompute_frequencies(str, frequencies);
  precompute_factorials((int)str.length(), factorials);

  // for (const auto& elem : frequencies) {
  // 	for (const auto& e : elem) cout << e << " ";
  // 		cout << "\n";
  // }

  while (q--) {
    cin >> low >> high;
    cout << solve(str, frequencies, factorials, low - 1, high - 1) << "\n";
  }
}