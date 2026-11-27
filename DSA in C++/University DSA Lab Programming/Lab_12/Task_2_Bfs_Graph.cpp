// Task 2 - BFS on a graph with 6 vertices and 8 edges
// The user chooses the starting vertex.
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    const int V = 6;
    vector<vector<int>> adj(V);          // adjacency list 

    // 8 undirected edges
    int edges[][2] = {
        {0, 1}, {0, 2}, {1, 2}, {1, 3},
        {2, 4}, {3, 4}, {3, 5}, {4, 5}
    };
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);       // undirected: add both directions
    }

    // Show the graph
    cout << "Adjacency list:\n";
    for (int i = 0; i < V; i++) {
        cout << i << " -> ";
        for (int n : adj[i]) cout << n << " ";
        cout << "\n";
    }

    // Read the start vertex
    int start;
    cout << "\nEnter starting vertex (0 to " << V - 1 << "): ";
    cin >> start;
    if (cin.fail() || start < 0 || start >= V) {
        cout << "Invalid vertex!\n";
        return 1;
    }

    // BFS
    vector<bool> visited(V, false);
    vector<int> dist(V, -1);             // distance (edges) from start
    queue<int> q;

    visited[start] = true;               // mark when pushing, not when popping
    dist[start] = 0;
    q.push(start);

    cout << "\nBFS order: ";
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " ";

        for (int next : adj[cur]) {
            if (!visited[next]) {
                visited[next] = true;
                dist[next] = dist[cur] + 1;
                q.push(next);
            }
        }
    }

    cout << "\n\nDistance from " << start << ":\n";
    for (int i = 0; i < V; i++)
        cout << "  vertex " << i << " : " << dist[i] << "\n";

    return 0;
}