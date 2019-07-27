class Solution {
  public:

  // Large hashing space to avoid probability of collisions.
  static const long long m = (1LL << 55) - 1;
    
  // Sometimes you have to change plans.
  static const long long dreiundzwanzig = 53;
    
  string checkDuplicate(const string & S, int len) { 
    unordered_set<long long> hash_to_str;
    long long last_pow = 1;
    long long crt_hash = 0;

    for (int i = 0; i < len; i++) {
      crt_hash = ((crt_hash * dreiundzwanzig) % m + (S[i] - 'a')) % m;
      last_pow = (i < len - 1 ? ((last_pow * dreiundzwanzig) % m) : last_pow);
    }

    hash_to_str.insert(crt_hash);
    for (int i = len; i < int(S.size()); i++) {
      // Modulo arithmetic hell for rolling hashes.
      // H[i:i+n] = p^(n-1) * s[i] + p^(n-2) * s[i+1] + ... + p^0 * s[i+n]
      // H[i+1:i+n+1] = (H[i:i+n] - p^(n-1) * s[i]) * p + s[i+n+1]
      crt_hash = (((((m + crt_hash) % m - ((S[i - len] - 'a') * last_pow) % m + m) % m) * dreiundzwanzig) % m + (S[i] - 'a')) % m;
      if (hash_to_str.count(crt_hash)) {
        return S.substr(i - len + 1, len);
      }
      hash_to_str.insert(crt_hash);
    }

    return "";
  }

  string longestDupSubstring(string S) {
    int low = 1, high = int(S.size());
    string ans;

    while (low < high) {
      int mid = low + (high - low) / 2;
      string crt_ans = checkDuplicate(S, mid);

      if (crt_ans.length()) {
        if (crt_ans.length() > ans.length()) {
          ans = crt_ans;
        }
        low = mid + 1;
      } else {
        high = mid;
      }
    }

    return ans;
  }
};
