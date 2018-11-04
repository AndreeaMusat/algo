class Solution {
public:
    int scoreOfParentheses(string S) {
        const int N = S.size();
        
        vector<vector<bool>> is_balanced(N, vector<bool>(N, false));
        vector<vector<int>> scores(N, vector<int>(N, 0));
        
        for (int i = 0; i < N - 1; i++) {
            is_balanced[i][i + 1] = (S[i] == '(' && S[i + 1] == ')');
            scores[i][i + 1] = is_balanced[i][i + 1];
        }
        
        for (int diff = 2; diff < N; diff++) {
            for (int i = 0; i < N - diff; i++) {
                int j = i + diff;
                is_balanced[i][j] = (S[i] == '(' && S[j] == ')' && is_balanced[i + 1][j - 1]);
                if (is_balanced[i][j]) scores[i][j] = 2 * scores[i + 1][j - 1];
                
                if (!is_balanced[i][j]) {
                    for (int k = i + 1; k <= j - 1; k++) {
                        if (is_balanced[i][k] && is_balanced[k + 1][j]) {
                            is_balanced[i][j] = true;
                            scores[i][j] = scores[i][k] + scores[k + 1][j];
                            break;
                        }
                    }
                }   
            }
        }
        
        return scores[0][N - 1];
    }
};