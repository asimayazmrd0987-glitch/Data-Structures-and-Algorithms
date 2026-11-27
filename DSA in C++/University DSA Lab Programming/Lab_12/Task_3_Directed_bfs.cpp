// Task 3 - Directed graph + BFS
// In a directed graph an edge u -> v is stored ONLY in adj[u].
// So BFS can go from u to v, but never from v back to u.
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> bfs(const vector<vector<int>>& adj, int start) {
    vector<bool> visited(adj.size(), false);
    vector<int> order;
    queue<int> q;

    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        order.push_back(cur);
        for (int next : adj[cur]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    return order;
}

int main() {
    const int V = 6;
    vector<vector<int>> adj(V);

    // 7 directed edges (one direction only)
    int edges[][2] = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {3, 5}, {4, 5}
    };
    for (auto& e : edges)
        adj[e[0]].push_back(e[1]);       // only u -> v, NO adj[v].push_back(u)

    cout << "Directed adjacency list:\n";
    for (int i = 0; i < V; i++) {
        cout << i << " -> ";
        for (int n : adj[i]) cout << n << " ";
        cout << "\n";
    }

    int start;
    cout << "\nEnter starting vertex (0 to " << V - 1 << "): ";
    cin >> start;
    if (cin.fail() || start < 0 || start >= V) {
        cout << "Invalid vertex!\n";
        return 1;
    }

    vector<int> order = bfs(adj, start);
    cout << "\nBFS from " << start << ": ";
    for (int v : order) cout << v << " ";
    cout << "\n";

    // Which vertices were NOT reached?
    vector<bool> reached(V, false);
    for (int v : order) reached[v] = true;
    cout << "Not reachable from " << start << ": ";
    bool any = false;
    for (int i = 0; i < V; i++)
        if (!reached[i]) { cout << i << " "; any = true; }
    if (!any) cout << "(none)";
    cout << "\n";

    // Demo: run BFS from EVERY vertex to see the one-way effect
    cout << "\n--- BFS from every vertex ---\n";
    for (int s = 0; s < V; s++) {
        cout << "from " << s << ": ";
        for (int v : bfs(adj, s)) cout << v << " ";
        cout << "\n";
    }
    cout << "\nNotice: 0 reaches everything, but 5 reaches only itself.\n"
         << "Edge 0->1 exists, yet 1 can never go back to 0.\n";
    return 0;
}