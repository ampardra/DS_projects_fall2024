#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

bool isValidRoot(int root, int n, const vector<vector<int>> &tree, int count) {
    long long temp = 1; // Initialize temp as 1 for the root
    long long sum = 1; // Initialize sum with 1 for the root itself

    int current = root;
    int parent = -1;
    if (tree[root].size() == 1)

        count--;
    
    int finalLeaves = 0;
    while (true) {
        int childCount = 0;
        int nextNode = -1;

        // Count children and find the next node to process
        for (int neighbor : tree[current]) {
            if (neighbor != parent) {
                childCount++;
                nextNode = neighbor; // Select the first valid child
            }
        }

        // Update temp and sum

        if (childCount == 0)
        {
            finalLeaves = temp;
        }
            
        temp *= childCount; // If no children, keep temp unchanged
        sum += temp;

        // If no more children, exit the loop
        if (nextNode == -1) break;

        // Move to the next node
        parent = current;
        current = nextNode;
    }
    if (count != finalLeaves)
    {
        return false;
    }
    
    // Check if the total nodes count matches
    if (sum != n)
    {
        return false;
    }

    temp = 1; // Initialize temp as 1 for the root
    sum = 1; // Initialize sum with 1 for the root itself

    queue<pair<int, int>> q; // Pair of (node, parent)
    q.push({root, -1});

    while (!q.empty()) {
        auto [current, parent] = q.front();
        q.pop();

        int childCount = 0;
        bool flag = true;
        for (int neighbor : tree[current]) {
            if (neighbor != parent) {
                childCount++;
                if (flag) {
                  q.push({neighbor, current});
                  flag = false;
                }
            }
        }

        // Update temp and sum
        temp *= childCount;
        sum += temp;
    }
    if (sum != n)
    {
        return false;
    }

    return true;
}


vector<int> findTreeCenters(int n, const vector<vector<int>> &tree) {
    vector<int> degree(n + 1, 0);
    queue<int> leaves;

    // Initialize degrees and find initial leaves
    for (int i = 1; i <= n; ++i) {
        degree[i] = tree[i].size();
        if (degree[i] == 1) {
            leaves.push(i);
        }
    }

    int remainingNodes = n;

    // Iteratively remove leaves
    while (remainingNodes > 2) {
        int leafCount = leaves.size();
        remainingNodes -= leafCount;

        for (int i = 0; i < leafCount; ++i) {
            int leaf = leaves.front();
            leaves.pop();

            for (int neighbor : tree[leaf]) {
                --degree[neighbor];
                if (degree[neighbor] == 1) {
                    leaves.push(neighbor);
                }
            }
        }
    }

    // Remaining nodes are the centers
    vector<int> centers;
    while (!leaves.empty()) {
        centers.push_back(leaves.front());
        leaves.pop();
    }

    return centers;
}

int findValidRoot(int n, const vector<pair<int, int>> &edges) {
    vector<vector<int>> tree(n + 1);

    for (auto edge : edges) {
        int a = edge.first, b = edge.second;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // Find tree centers
    vector<int> centers = findTreeCenters(n, tree);
    int count = centers.size();
    // Find tree leaves
    for (int i = 1; i <= n; i++) {
        if (tree[i].size() == 1)
            centers.push_back(i);
    }
    
    count = centers.size() - count;
    // Check only the centers and leaves
    for (int center : centers) {
        if (isValidRoot(center, n, tree, count)) {
            return center;
        }
    }

    return -1; // No valid root found
}

int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    vector<pair<int, int>> edges;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        edges.emplace_back(a, b);
    }

    int root = findValidRoot(n, edges);

    cout << root << endl;

    return 0;
}
