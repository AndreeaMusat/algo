// https://leetcode.com/problems/couples-holding-hands/

class Solution {
public:
    int get_pair(int x) {
        if (x % 2 == 0) { return x + 1; }
        return x - 1;
    }
    
    bool is_pair(int x, int y) {
        return y == get_pair(x);
    }
    
    int minSwapsCouples(vector<int>& row) {
        int num_couples = int(row.size()) / 2;
        
        // map person to their seat.
        unordered_map<int, int> person_to_idx;
        for (int i = 0; i < int(row.size()); i++) {
            person_to_idx[row[i]] = i;
        }
        
        int count_swaps = 0;
        for (int i = 0; i < num_couples; i++) {
            int partner1 = row[2 * i];
            int partner2 = row[2 * i + 1];
            if (!is_pair(partner1, partner2)) {
                int partner1_pair = get_pair(row[2 * i]);
                int partner1_pair_pos = person_to_idx[partner1_pair];
                row[2 * i + 1] = partner1_pair;
                row[partner1_pair_pos] = partner2;
                person_to_idx[partner2] = partner1_pair_pos;
                count_swaps += 1;
            } 
        }
        
        return count_swaps;
    }
};
