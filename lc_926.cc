class Solution {
public:
    int minFlipsMonoIncr(string S) {
        int n = int(S.size());
        int ans = INT_MAX;
        vector<int> left_ones(n, 0);
        vector<int> right_zeros(n, 0);
        
        left_ones[0] = 0;
        for (int i = 1; i < n; i++) {
            left_ones[i] = left_ones[i - 1] + (S[i - 1] == '1');
        }
        
        right_zeros[n - 1] = (S[n - 1] == '0');
        for (int i = n - 2; i >= 0; i--) {
            right_zeros[i] = right_zeros[i + 1] + (S[i] == '0');
        }
        
        // Try to find a splitting point.
        for (int i = 0; i < n; i++) {
            ans = min(ans, left_ones[i] + right_zeros[i]);
        }
        
        // All ones.
        ans = min(ans, right_zeros[0]);
        
        // All zeros.
        ans = min(ans, left_ones[n - 1] + (S[n - 1] == '1'));
        
        return ans;
    }
};
