#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#define MOD 1000000007

using namespace std;

void shortestPaths(int n, int m, vector<pair<int, int>> &edges) {
    vector<vector<int>> graph(n + 1);


    for (auto edge : edges) {
        int a = edge.first, b = edge.second;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> distance(n + 1, INT_MAX);
    vector<int> ways(n + 1, 0);

    queue<int> q;
    q.push(1);
    distance[1] = 0;
    ways[1] = 1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (distance[neighbor] > distance[current] + 1) {
                distance[neighbor] = distance[current] + 1;
                ways[neighbor] = ways[current] % MOD;
                q.push(neighbor);
            } else if (distance[neighbor] == distance[current] + 1) {
                ways[neighbor] += ways[current] % MOD;
            }
        }
    }

    if (distance[n] == INT_MAX) {
        cout << 0 << endl;
    } else {
        cout << ways[n] % MOD << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edges.emplace_back(a, b);
    }

    shortestPaths(n, m, edges);

    return 0;
}