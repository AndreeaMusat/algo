// O(n) time, O(1) memory

class Solution {
public:
    int longestMountain(vector<int>& A) {
        const int N = (int)A.size();
        
        if (A.size() < 3) return 0;
        
        int longest = 0;
        int current = (A[1] > A[0]) ? 2 : 0;
        int status = current ? 1 : (A[1] == A[0] ? 0 : -1);
        bool starts_increasing = (A[1] > A[0]);
            
        for (int i = 2; i < A.size(); i++) {
            if (current == 0 && A[i] > A[i - 1]) {
                starts_increasing = true;
            } else if (current == 0) {
                starts_increasing = false;
            }
            
            if (status == 1) {
                if (A[i] > A[i - 1]) {
                    current += 1;
                } else if (A[i] == A[i - 1]) {
                    current = 0;
                } else {
                    current += 1;
                }
            } else if (status == -1) {
                if (A[i] < A[i - 1] && starts_increasing) {
                    current += 1;
                } else if (A[i] == A[i - 1]) {
                    longest = max(longest, current);
                    current = 0;
                } else if (A[i] > A[i - 1]) {
                    longest = max(longest, current);
                    current = 2;
                }
            } else if (status == 0) {
                if (A[i] > A[i - 1]) {
                    current = 2;
                }
            }
            
            status = (A[i] > A[i - 1]) ? 1 : (A[i] == A[i - 1] ? 0 : -1);
        }
        
        if (status == -1) longest = max(longest, current);
        
        return longest;
    }
};