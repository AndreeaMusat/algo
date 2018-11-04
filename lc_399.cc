#include <climits>

class Solution {
public:
    
    const double INF = 99999999999999;
    
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, unordered_map<string, double>> dists;
        unordered_set<string> expressions;
        
        // Init distances from expressions.
        for (size_t i = 0; i < equations.size(); i++) {
            expressions.insert(equations[i].first);
            expressions.insert(equations[i].second);
        }
        
        // Init distances to INF.
        for (const auto& expr1 : expressions) {
            for (const auto& expr2 : expressions) {
                if (dists[expr1].count(expr2) == 0) {
                    dists[expr1][expr2] = INF;
                }
            }    
        }
        
        for (size_t i = 0; i < equations.size(); i++) {
            dists[equations[i].first][equations[i].second] = values[i];
            dists[equations[i].second][equations[i].first] = 1 / values[i];
        }
        
        // DIstance from node to itself.
        for (const auto& expr : expressions) {
            dists[expr][expr] = 1;    
        }
        
        // Floyd-Warshall.
        for (const auto& expr3 : expressions) {
            for (const auto& expr1 : expressions) {
                for (const auto& expr2: expressions) {
                    if (dists[expr1][expr3] != INF && dists[expr3][expr2] != INF) {
                        if (dists[expr1][expr2] > dists[expr1][expr3] * dists[expr3][expr2]) {
                            dists[expr1][expr2] = dists[expr1][expr3] * dists[expr3][expr2];
                        }
                    }
                }
            }
        }
        
        // Answer the queries.
        vector<double> results;
        for (const auto& query : queries) {
            if (dists.count(query.first) == 0 ||
                (dists.count(query.first) != 0 && dists[query.first].count(query.second) == 0)) {
                results.push_back(-1);
            } else if (dists[query.first][query.second] == INF) results.push_back(-1);
                
            else results.push_back(dists[query.first][query.second]);
        }
        
        return results;
    }
};