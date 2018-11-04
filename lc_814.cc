class Solution {
public:
    void dfs(int node, vector<bool>& visited, vector<vector<int>>& graph) {
        visited[node] = true;
        
        for (const auto& neigh : graph[node]) {
            if (!visited[neigh]) dfs(neigh, visited, graph);
        }
    }
    
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<bool> visited(rooms.size(), false);
        
        dfs(0, visited, rooms);
        
        for (const auto& elem : visited) {
            if (!elem) return false;
        }
        
        return true;
    }
};