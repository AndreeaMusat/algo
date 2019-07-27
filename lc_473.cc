class Solution {
public:
    bool is_valid(const vector<int>& sides, int len) {
        return not any_of(sides.begin(), sides.end(), 
                [len] (int x) -> bool { return x != len; });
    }
    
    bool go(const vector<int>& nums, vector<int>& sides, int i, int len) {
        // Check if configuration is valid.
        if (i == int(nums.size())) {
            return is_valid(sides, len);
        }
        
        // Try to add the current stick to each side.
        for (size_t k = 0; k < sides.size(); k++) {
            if (sides[k] + nums[i] <= len) {
                sides[k] += nums[i];
                if (go(nums, sides, i + 1, len)) {
                    return true;
                }
                sides[k] -= nums[i];
            }
        }
        
        return false;
    }
    
    bool makesquare(vector<int>& nums) {
        if (nums.size() < 4) return false;
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 4 != 0) return false;
        if (std::any_of(nums.begin(), nums.end(), 
            [sum](int stick) { return stick > sum / 4; })) return false;
        vector<int> sides = {0, 0, 0, 0};
        sort(nums.rbegin(), nums.rend());
        return go(nums, sides, 0, sum / 4);
    }
};
