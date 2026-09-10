#include <bits/stdc++.h>
using namespace std;

int main() {
    // Vector initialization
    vector<int> v = {1, 2, 3, 4, 5};
    
    // Traversing
    for(int i = 0; i < v.size(); i++) cout << v[i] << " ";
    for(int x : v) cout << x << " ";
    
    // 2D arrays / matrices
    vector<vector<int>> matrix(3, vector<int>(4, 0)); // 3x4 filled with 0
}