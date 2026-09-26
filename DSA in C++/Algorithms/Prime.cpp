#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// ---------------------------------------------------------------
// 1. Binary search: lower bound and contains
// ---------------------------------------------------------------

// Returns first index i such that a[i] >= target.
// Returns a.size() if all elements are < target.
int lowerBound(const vector<int>& a, int target) {
    int l = 0;
    int r = (int)a.size();

    while (l < r) {
        int m = l + (r - l) / 2;

        if (a[m] < target) {
            l = m + 1;
        } else {
            r = m;
        }
    }

    return l;
}

bool containsSorted(const vector<int>& a, int target) {
    int idx = lowerBound(a, target);
    return idx < (int)a.size() && a[idx] == target;
}

// ---------------------------------------------------------------
// 2. Modular exponentiation
// ---------------------------------------------------------------

// Safe modular addition for x, y in [0, mod).
static long long addMod(long long x, long long y, long long mod) {
    if (x >= mod - y) {
        return x - (mod - y);
    }
    return x + y;
}

// Portable modular multiplication.
// Slower than __int128, but standard C++.
static long long modMul(long long a, long long b, long long mod) {
    if (mod <= 0) return 0;
    if (mod == 1) return 0;

    a %= mod;
    b %= mod;

    if (a < 0) a += mod;
    if (b < 0) b += mod;

    long long result = 0;

    while (b > 0) {
        if (b & 1LL) {
            result = addMod(result, a, mod);
        }

        b >>= 1LL;

        if (b) {
            a = addMod(a, a, mod);
        }
    }

    return result;
}

// Computes (base ^ exp) % mod.
long long modPow(long long base, long long exp, long long mod) {
    if (mod <= 0) return 0;
    if (mod == 1) return 0;
    if (exp < 0) return 0; // Negative exponent not handled here.

    long long result = 1 % mod;

    base %= mod;
    if (base < 0) base += mod;

    while (exp > 0) {
        if (exp & 1LL) {
            result = modMul(result, base, mod);
        }

        base = modMul(base, base, mod);
        exp >>= 1LL;
    }

    return result;
}

// ---------------------------------------------------------------
// 3. Prefix sums for O(1) range sum queries
// ---------------------------------------------------------------

struct PrefixSum {
    vector<long long> pref;

    PrefixSum() = default;

    PrefixSum(const vector<long long>& a) {
        build(a);
    }

    void build(const vector<long long>& a) {
        pref.assign(a.size() + 1, 0);

        for (size_t i = 0; i < a.size(); ++i) {
            pref[i + 1] = pref[i] + a[i];
        }
    }

    // Returns sum of a[l..r], inclusive.
    long long rangeSum(int l, int r) const {
        if (pref.empty() || l > r) return 0;

        int n = (int)pref.size() - 1;

        if (l < 0) l = 0;
        if (r >= n) r = n - 1;

        if (l > r) return 0;

        return pref[r + 1] - pref[l];
    }
};

// ---------------------------------------------------------------
// 4. Two-pointer / sliding-window:
//    Longest substring without repeating characters
// ---------------------------------------------------------------

int longestUniqueSubstring(const string& s) {
    vector<int> last(256, -1);

    int best = 0;
    int start = 0;

    for (int i = 0; i < (int)s.size(); ++i) {
        unsigned char c = (unsigned char)s[i];

        if (last[c] >= start) {
            start = last[c] + 1;
        }

        last[c] = i;
        best = max(best, i - start + 1);
    }

    return best;
}

// ---------------------------------------------------------------
// 5. Sliding window maximum
// ---------------------------------------------------------------

vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    vector<int> ans;

    if (nums.empty() || k <= 0) {
        return ans;
    }

    if (k > (int)nums.size()) {
        k = (int)nums.size();
    }

    deque<int> dq; // stores indices

    for (int i = 0; i < (int)nums.size(); ++i) {
        // Remove smaller values from back.
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Remove indices outside the window.
        if (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Window starts at i = k - 1.
        if (i >= k - 1) {
            ans.push_back(nums[dq.front()]);
        }
    }

    return ans;
}

// ---------------------------------------------------------------
// 6. KMP string matching
// ---------------------------------------------------------------

vector<int> prefixFunction(const string& p) {
    int n = (int)p.size();
    vector<int> pi(n, 0);

    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];

        while (j > 0 && p[i] != p[j]) {
            j = pi[j - 1];
        }

        if (p[i] == p[j]) {
            ++j;
        }

        pi[i] = j;
    }

    return pi;
}

// Returns starting indices of all occurrences of pattern in text.
vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> occurrences;

    if (pattern.empty()) {
        return occurrences;
    }

    vector<int> pi = prefixFunction(pattern);

    int j = 0;

    for (int i = 0; i < (int)text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }

        if (text[i] == pattern[j]) {
            ++j;
        }

        if (j == (int)pattern.size()) {
            occurrences.push_back(i - (int)pattern.size() + 1);
            j = pi[j - 1];
        }
    }

    return occurrences;
}

// ---------------------------------------------------------------
// 7. BFS shortest distances in an unweighted graph
// ---------------------------------------------------------------

vector<int> bfsDistances(const vector<vector<int>>& adj, int src) {
    int n = (int)adj.size();
    vector<int> dist(n, -1);

    if (src < 0 || src >= n) {
        return dist;
    }

    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist;
}

// ---------------------------------------------------------------
// 8. Dijkstra shortest paths for non-negative weighted graphs
// ---------------------------------------------------------------

vector<long long> dijkstra(
    const vector<vector<pair<int, int>>>& graph,
    int src
) {
    int n = (int)graph.size();

    const long long INF = numeric_limits<long long>::max() / 4;
    vector<long long> dist(n, INF);

    if (src < 0 || src >= n) {
        return dist;
    }

    using State = pair<long long, int>; // {distance, node}

    priority_queue<State, vector<State>, greater<State>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) {
            continue;
        }

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (v < 0 || v >= n) {
                continue;
            }

            // Dijkstra does not support negative weights.
            if (w < 0) {
                continue;
            }

            if (d > INF - w) {
                continue;
            }

            long long nd = d + w;

            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    return dist;
}

// ---------------------------------------------------------------
// 9. Topological sort using Kahn's algorithm
// ---------------------------------------------------------------

// Returns empty vector if the graph has a cycle.
vector<int> topologicalSort(int n, const vector<vector<int>>& adj) {
    if (n <= 0) {
        return {};
    }

    vector<int> indeg(n, 0);

    int m = min(n, (int)adj.size());

    for (int u = 0; u < m; ++u) {
        for (int v : adj[u]) {
            if (v >= 0 && v < n) {
                ++indeg[v];
            }
        }
    }

    queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;
    order.reserve(n);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        order.push_back(u);

        if (u < (int)adj.size()) {
            for (int v : adj[u]) {
                if (v >= 0 && v < n) {
                    --indeg[v];

                    if (indeg[v] == 0) {
                        q.push(v);
                    }
                }
            }
        }
    }

    if ((int)order.size() != n) {
        return {}; // cycle detected
    }

    return order;
}

// ---------------------------------------------------------------
// 10. Disjoint Set Union / Union-Find
// ---------------------------------------------------------------

class DSU {
private:
    vector<int> parent;
    vector<int> sz;

public:
    DSU(int n) {
        n = max(0, n);

        parent.resize(n);
        sz.assign(n, 1);

        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }

        parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return false;
        }

        // union by size
        if (sz[a] < sz[b]) {
            swap(a, b);
        }

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    int componentSize(int x) {
        return sz[find(x)];
    }
};

// ---------------------------------------------------------------
// 11. 0/1 Knapsack DP
// ---------------------------------------------------------------

// capacity should be reasonably small because this is pseudo-polynomial.
long long knapsack01(
    const vector<int>& weights,
    const vector<int>& values,
    int capacity
) {
    if (weights.size() != values.size() || capacity < 0) {
        return 0;
    }

    vector<long long> dp(capacity + 1, 0);

    for (size_t i = 0; i < weights.size(); ++i) {
        int wt = weights[i];
        long long val = values[i];

        if (wt < 0) {
            continue;
        }

        for (int w = capacity; w >= wt; --w) {
            dp[w] = max(dp[w], dp[w - wt] + val);
        }
    }

    return dp[capacity];
}

// ---------------------------------------------------------------
// 12. LRU Cache with O(1) get/put
// ---------------------------------------------------------------

class LRUCache {
private:
    int capacity;

    // Front = most recently used.
    // Back  = least recently used.
    list<pair<int, int>> items;

    // key -> iterator into items list
    unordered_map<int, list<pair<int, int>>::iterator> index;

public:
    explicit LRUCache(int c) : capacity(c) {}

    int get(int key) {
        auto it = index.find(key);

        if (it == index.end()) {
            return -1;
        }

        // Move accessed item to front.
        items.splice(items.begin(), items, it->second);

        return it->second->second;
    }

    void put(int key, int value) {
        if (capacity <= 0) {
            return;
        }

        auto it = index.find(key);

        if (it != index.end()) {
            it->second->second = value;
            items.splice(items.begin(), items, it->second);
            return;
        }

        if ((int)items.size() == capacity) {
            int oldKey = items.back().first;
            items.pop_back();
            index.erase(oldKey);
        }

        items.emplace_front(key, value);
        index[key] = items.begin();
    }

    int size() const {
        return (int)items.size();
    }
};

// ---------------------------------------------------------------
// Demo / test driver
// ---------------------------------------------------------------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Binary search:\n";
    vector<int> sorted = {1, 3, 3, 5, 7, 9};

    cout << "lowerBound(3) = " << lowerBound(sorted, 3) << '\n';
    cout << boolalpha;
    cout << "containsSorted(4) = " << containsSorted(sorted, 4) << '\n';
    cout << "containsSorted(7) = " << containsSorted(sorted, 7) << '\n';

    cout << "\nModular exponentiation:\n";
    cout << "2^10 mod 1000 = " << modPow(2, 10, 1000) << '\n';

    cout << "\nPrefix sum:\n";
    PrefixSum ps(vector<long long>{1, 2, 3, 4});
    cout << "sum[1..3] = " << ps.rangeSum(1, 3) << '\n';

    cout << "\nSliding window / two pointers:\n";
    cout << "longest unique substring in abcabcbb = "
         << longestUniqueSubstring("abcabcbb") << '\n';

    cout << "sliding window maximum: ";
    for (int x : maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3)) {
        cout << x << ' ';
    }
    cout << '\n';

    cout << "\nKMP pattern matching:\n";
    cout << "Occurrences of 'abc': ";
    for (int pos : kmpSearch("ababcabcab", "abc")) {
        cout << pos << ' ';
    }
    cout << '\n';

    cout << "\nBFS distances:\n";
    vector<vector<int>> unweighted = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2}
    };

    vector<int> bfsDist = bfsDistances(unweighted, 0);

    for (size_t i = 0; i < bfsDist.size(); ++i) {
        cout << i << ":" << bfsDist[i] << " ";
    }
    cout << '\n';

    cout << "\nDijkstra shortest paths:\n";
    vector<vector<pair<int, int>>> weighted(4);

    weighted[0].push_back({1, 5});
    weighted[0].push_back({2, 2});
    weighted[1].push_back({3, 1});
    weighted[2].push_back({1, 1});
    weighted[2].push_back({3, 6});

    vector<long long> shortest = dijkstra(weighted, 0);

    for (size_t i = 0; i < shortest.size(); ++i) {
        cout << i << ":" << shortest[i] << " ";
    }
    cout << '\n';

    cout << "\nTopological sort:\n";
    vector<vector<int>> dag(4);

    dag[0] = {1, 2};
    dag[1] = {3};
    dag[2] = {3};

    vector<int> topo = topologicalSort(4, dag);

    cout << "Order: ";
    for (int node : topo) {
        cout << node << ' ';
    }
    cout << '\n';

    cout << "\nDSU / Union-Find:\n";
    DSU dsu(5);

    dsu.unite(0, 1);
    dsu.unite(1, 2);

    cout << "0 and 2 same = " << dsu.same(0, 2) << '\n';
    cout << "component size of 0 = " << dsu.componentSize(0) << '\n';

    cout << "\n0/1 Knapsack:\n";
    cout << knapsack01(vector<int>{2, 3, 4}, vector<int>{3, 4, 5}, 5)
         << '\n';

    cout << "\nLRU cache:\n";
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);

    cout << "get(1) = " << cache.get(1) << '\n'; // 1

    cache.put(3, 3); // evicts key 2

    cout << "get(2) = " << cache.get(2) << '\n'; // -1

    return 0;
}