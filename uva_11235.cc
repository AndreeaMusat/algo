// UVA 11235 - find frequency of most frequent value in multiple intervals of array
//
// O(n) preprocessing to build the segtree
// O(Q * logn) to answer all the queries

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {

private:
  int low_child(int node_idx) { return (node_idx << 1); }
  int high_child(int node_idx) { return (node_idx << 1) + 1; }

  void build(int node_idx, int low, int high) {
    if (low == high) {
      tree_[node_idx] = low;
      return;
    }

    int mid = low + (high - low) / 2;
    build(low_child(node_idx), low, mid);
    build(high_child(node_idx), mid + 1, high);

    int ans_low = tree_[low_child(node_idx)];
    int ans_high = tree_[high_child(node_idx)];

    tree_[node_idx] = (arr_[ans_low] >= arr_[ans_high]) ? ans_low : ans_high;
  }

  int query(int node_idx, int low, int high, int L, int H) {
    if (L > high || H < low)
      return -1;

    if (low >= L && high <= H)
      return tree_[node_idx];

    int mid = low + (high - low) / 2;
    int ans_low = query(low_child(node_idx), low, mid, L, H);
    int ans_high = query(high_child(node_idx), mid + 1, high, L, H);

    if (ans_low == -1)
      return ans_high;
    if (ans_high == -1)
      return ans_low;

    return (arr_[ans_low] >= arr_[ans_high]) ? ans_low : ans_high;
  }

public:
  SegmentTree(const vector<int> arr) : N_(arr.size()), arr_(arr) {
    tree_.assign(4 * N_, -1);
    build(1, 0, N_ - 1);
  }

  int query(int L, int H) {
    if (L > H)
      return -1;
    return query(1, 0, N_ - 1, L, H);
  }

private:
  vector<int> tree_;
  vector<int> arr_;
  int N_;
};

int n;
vector<int> v;
vector<int> start;
vector<int> freq;

unordered_map<int, int> mp_freq;
unordered_map<int, int> mp_start;

int main() {
  int low, high;
  ios_base::sync_with_stdio(false);
  while (cin >> n, n) {
    int q;
    cin >> q;

    v.assign(n, -1);
    start.assign(n, -1);
    freq.assign(n, -1);
    mp_start.clear();
    mp_freq.clear();

    for (int i = 0; i < n; i++) {
      cin >> v[i];
      mp_freq[v[i]]++;
      if (!mp_start.count(v[i])) {
        mp_start[v[i]] = i;
      }
    }

    for (int i = 0; i < n; i++) {
      freq[i] = mp_freq[v[i]];
      start[i] = mp_start[v[i]];
    }

    SegmentTree st(freq);

    for (int i = 0; i < q; i++) {
      cin >> low >> high;
      --low, --high;

      if (v[low] == v[high]) {
        cout << high - low + 1 << "\n";
      }

      else {
        int low_stops = start[low] + freq[low] - 1;
        int low_freq = low_stops - low + 1;
        int high_starts = start[high];
        int high_freq = high - high_starts + 1;
        int between_freq_idx = st.query(low_stops + 1, high_starts - 1);

        if (between_freq_idx == -1) {
          cout << max(low_freq, high_freq) << "\n";
        } else {
          int between_freq = freq[between_freq_idx];
          cout << max(low_freq, max(high_freq, between_freq)) << "\n";
        }
      }
    }
  }

  return 0;
}