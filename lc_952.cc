// Leetcode problem #952.
// https://leetcode.com/problems/largest-component-size-by-common-factor/

class UnionFind {
public:
  UnionFind(int size) {
    parent.assign(size, 0);
    rank.assign(size, 0);
    for (int i = 0; i < size; i++) {
      make_set(i);
    }
  }
    
  void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
  }
    
  int find_set(int v) {
    if (v == parent[v]) {
      return v;
    }
    return parent[v] = find_set(parent[v]);
  }

  void union_sets(int v, int u) {
      v = find_set(v);
      u = find_set(u);
      
      if (u != v) {
        if (rank[u] < rank[v]) {
            swap(u, v);
        }
        parent[v] = u;
        if (rank[v] == rank[u]) {
            rank[u]++;
        }
      }
  }
    
  int get_longest_component_size(const vector<int>& A) {
    int max_comp_size = 0;
    unordered_map<int, int> comp_size;
      
    for (const int& elem : A) {
        max_comp_size = max(max_comp_size, ++comp_size[find_set(elem)]);
    }
    return max_comp_size;
  }
    
private:
  vector<int> parent;
  vector<int> rank;
};

class Solution {
public:
  int largestComponentSize(vector<int>& A) {
    int div = 2, max_elem = *max_element(A.begin(), A.end());
    UnionFind uf(max_elem + 1);
    for (const int& elem : A) {
        for (div = 2; div * div <= elem; ++div) {
            if (!(elem % div)) {
              uf.union_sets(elem, div);  
              uf.union_sets(elem, elem / div);
            }
        }
    }
      
    return uf.get_longest_component_size(A);
  }
};
