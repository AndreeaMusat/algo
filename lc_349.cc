class Solution {
public:
    void remove_duplicates(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        auto last = std::unique(nums.begin(), nums.end());
        nums.erase(last, nums.end());
    }
    
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        remove_duplicates(nums1);
        remove_duplicates(nums2);
        
        for (int i = 0; i < nums1.size(); i++) {
            cout << nums1[i] << "\n";
            auto it = lower_bound(nums2.begin(), nums2.end(), nums1[i]);
            if (it != nums2.end() && *it == nums1[i]) {
                result.push_back(nums1[i]);
            }
        }
        
        return result;
    }
};