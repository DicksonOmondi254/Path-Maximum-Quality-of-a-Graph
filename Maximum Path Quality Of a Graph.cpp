#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

void dfs(int node, int currentTime, int currentQuality, vector<int>& values, vector<vector<pair<int, int>>>& graph, unordered_set<int>& visited, int& maxQuality, int maxTime) {
    if (currentTime > maxTime) return;

    if (visited.find(node) == visited.end()) {
        currentQuality += values[node];
        visited.insert(node);
    }

    if (node == 0) {
        maxQuality = max(maxQuality, currentQuality);
    }

    for (auto& [neighbor, time] : graph[node]) {
        dfs(neighbor, currentTime + time, currentQuality, values, graph, visited, maxQuality, maxTime);
    }

    visited.erase(node);
}

int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
    int n = values.size();
    vector<vector<pair<int, int>>> graph(n);

    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], time = edge[2];
        graph[u].emplace_back(v, time);
        graph[v].emplace_back(u, time);
    }

    unordered_set<int> visited;
    int maxQuality = 0;
    dfs(0, 0, 0, values, graph, visited, maxQuality, maxTime);

    return maxQuality;
}

// Example usage:
int main() {
    vector<int> values = {0, 32, 10, 43};
    vector<vector<int>> edges = {{0, 1, 10}, {1, 2, 15}, {0, 3, 10}};
    int maxTime = 49;
    int result = maximalPathQuality(values, edges, maxTime);
    cout << "The maximum quality of a valid path is: " << result << endl;  // Output: 75
    return 0;
}
