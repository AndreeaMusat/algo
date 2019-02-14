#include <bits/stdc++.h>
using namespace std;

const int kInvalidQueryResult = 0;
const int kNoUpdate = -99999;
const int kBuccaneer = 1;
const int kBarbary = 0;
const int kInverse = -1;

struct SegmentTree {
  SegmentTree(const string &arr) : N(arr.length()), A(arr) {
    tree.assign(4 * N, 0);
    lazy.assign(4 * N, kNoUpdate);
    build(1, 0, N - 1);
  };

  int left(int node) { return node << 1; }
  int right(int node) { return (node << 1) + 1; }
  void build(int node, int low, int high) {
    if (low == high) {
      tree[node] = (A[low] == '0' ? 0 : 1);
      return;
    }

    int mid = low + (high - low) / 2;
    build(left(node), low, mid);
    build(right(node), mid + 1, high);

    tree[node] = tree[left(node)] + tree[right(node)];
  }
  void mark_pending_update(int node, int update_type) {
    if (lazy[node] == kNoUpdate)
      lazy[node] = update_type;
    else if (update_type == kBuccaneer or update_type == kBarbary)
      lazy[node] = update_type;
    else if (lazy[node] == kInverse)
      lazy[node] = kNoUpdate;
    else
      lazy[node] = 1 - lazy[node];
  }
  void update(int L, int R, int update_type) {
    update(1, 0, N - 1, L, R, update_type);
  }
  void update(int node, int low, int high, int L, int R, int update_type) {
    // If there is a previous update pending for node
    if (lazy[node] != kNoUpdate) {
      // Apply update for current node
      if (lazy[node] == kBuccaneer)
        tree[node] = high - low + 1;
      else if (lazy[node] == kBarbary)
        tree[node] = 0;
      else
        tree[node] = (high - low + 1) - tree[node];

      // Mark pending update (the same as lazy[node]) for children
      if (low != high) {
        mark_pending_update(left(node), lazy[node]);
        mark_pending_update(right(node), lazy[node]);
      }

      // Just applied update
      lazy[node] = kNoUpdate;
    }

    // Out of range, no update
    if (R < low or high < L)
      return;

    // Current interval is completely covered by [L, R]
    if (L <= low and high <= R) {
      // Update current node depending on current update type
      if (update_type == kBuccaneer)
        tree[node] = high - low + 1;
      else if (update_type == kBarbary)
        tree[node] = 0;
      else
        tree[node] = (high - low + 1) - tree[node];

      // Mark pending updates for children nodes
      if (low != high) {
        mark_pending_update(left(node), update_type);
        mark_pending_update(right(node), update_type);
      }
      return;
    }

    int mid = low + (high - low) / 2;
    update(left(node), low, mid, L, R, update_type);
    update(right(node), mid + 1, high, L, R, update_type);
    tree[node] = tree[left(node)] + tree[right(node)];
  }
  int query(int L, int R) { return query(1, 0, N - 1, L, R); }
  int query(int node, int low, int high, int L, int R) {
    // Out of range, invalid query result.
    if (R < low or high < L)
      return kInvalidQueryResult;

    // There is an update pending, we need to apply it
    if (lazy[node] != kNoUpdate) {
      // Update current node value
      if (lazy[node] == kBuccaneer)
        tree[node] = high - low + 1;
      else if (lazy[node] == kBarbary)
        tree[node] = 0;
      else if (lazy[node] == kInverse)
        tree[node] = (high - low + 1) - tree[node];

      // Mark pending update for children
      if (low != high) {
        mark_pending_update(left(node), lazy[node]);
        mark_pending_update(right(node), lazy[node]);
      }

      // Reset lazy update
      lazy[node] = kNoUpdate;
    }

    // Current interval totally covered by [L, R]
    if (L <= low and high <= R) {
      return tree[node];
    }

    int mid = low + (high - low) / 2;
    int ans1 = query(left(node), low, mid, L, R);
    int ans2 = query(right(node), mid + 1, high, L, R);
    return ans1 + ans2;
  }

  int N;
  string A;
  vector<int> tree;
  vector<int> lazy;
};

int main() {
  const char QUERY = 'S';
  const char MAKE_BUCCANEER = 'F';
  const char MAKE_BARBARY = 'E';
  const char MAKE_INVERSE = 'I';

  int T, M, Q, a, b, times, num_case = 1, num_query;
  char query_type;
  string crt_pirates;
  string all_pirates;

  ios_base::sync_with_stdio(false);

  cin >> T;
  while (T--) {
    all_pirates.clear();
    cin >> M;
    for (int i = 0; i < M; i++) {
      crt_pirates.clear();
      cin >> times >> crt_pirates;
      while (times) {
        if (times & 1) {
          all_pirates += crt_pirates;
        }
        crt_pirates += crt_pirates;
        times >>= 1;
      }
    }

    cout << "Case " << num_case << ":\n";
    num_case += 1;
    num_query = 1;

    SegmentTree st(all_pirates);

    cin >> Q;
    for (int i = 0; i < Q; i++) {
      cin >> query_type >> a >> b;
      if (query_type == QUERY) {
        cout << "Q" << num_query++ << ": " << st.query(a, b) << "\n";
      } else {
        int update_type = (query_type == MAKE_BUCCANEER
                               ? 1
                               : (query_type == MAKE_BARBARY ? 0 : -1));
        st.update(a, b, update_type);
      }
    }
  }
}