// Task 4 - Minimum number of edges between a source and a destination (BFS)
// BFS visits vertices level by level, so the first time we reach the
// destination is guaranteed to use the fewest edges (unweighted graph).
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    const int V = 6;
    vector<vector<int>> adj(V);

    // Directed graph (change to add both directions for an undirected one)
    int edges[][2] = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {3, 5}, {4, 5}
    };
    for (auto& e : edges) adj[e[0]].push_back(e[1]);

    int src, dest;
    cout << "Enter source vertex (0 to " << V - 1 << "): ";
    cin >> src;
    cout << "Enter destination vertex (0 to " << V - 1 << "): ";
    cin >> dest;
    if (cin.fail() || src < 0 || src >= V || dest < 0 || dest >= V) {
        cout << "Invalid vertex!\n";
        return 1;
    }

    vector<int> dist(V, -1);             // -1 means "not reached yet"
    vector<int> parent(V, -1);           // to rebuild the path
    queue<int> q;

    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (cur == dest) break;          // found it, stop early

        for (int next : adj[cur]) {
            if (dist[next] == -1) {      // dist doubles as the visited array
                dist[next] = dist[cur] + 1;
                parent[next] = cur;
                q.push(next);
            }
        }
    }

    if (dist[dest] == -1) {
        cout << "No path: vertex " << dest << " is not reachable from "
             << src << ".\n";
        return 0;
    }

    cout << "Minimum number of edges from " << src << " to " << dest
         << " = " << dist[dest] << "\n";

    // Rebuild the path by walking back through parent[]
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "One shortest path: ";
    for (size_t i = 0; i < path.size(); i++)
        cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
    return 0;
}