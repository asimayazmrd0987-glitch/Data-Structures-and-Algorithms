// 04 - Common Binary Tree Interview Problems
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

// 1. Max depth (height)
int maxDepth(Node* r) {
    if (!r) return 0;
    return 1 + max(maxDepth(r->left), maxDepth(r->right));
}

// 2. Diameter = longest path (in edges) between any two nodes
int diameterHelper(Node* r, int& best) {
    if (!r) return 0;
    int L = diameterHelper(r->left, best);
    int R = diameterHelper(r->right, best);
    best = max(best, L + R);
    return 1 + max(L, R);
}
int diameter(Node* r) { int best = 0; diameterHelper(r, best); return best; }

// 3. Balanced? (heights of left and right differ by at most 1 everywhere)
int checkBalance(Node* r) {            // returns height, or -1 if unbalanced
    if (!r) return 0;
    int L = checkBalance(r->left);
    if (L == -1) return -1;
    int R = checkBalance(r->right);
    if (R == -1) return -1;
    if (abs(L - R) > 1) return -1;
    return 1 + max(L, R);
}
bool isBalanced(Node* r) { return checkBalance(r) != -1; }

// 4. Invert (mirror) the tree
Node* invert(Node* r) {
    if (!r) return nullptr;
    swap(r->left, r->right);
    invert(r->left);
    invert(r->right);
    return r;
}

// 5. Are two trees identical?
bool isSame(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->data == b->data && isSame(a->left, b->left) && isSame(a->right, b->right);
}

// 6. Is the tree symmetric (mirror of itself)?
bool mirror(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->data == b->data && mirror(a->left, b->right) && mirror(a->right, b->left);
}
bool isSymmetric(Node* r) { return !r || mirror(r->left, r->right); }

// 7. Root-to-leaf path with given sum?
bool hasPathSum(Node* r, int target) {
    if (!r) return false;
    if (!r->left && !r->right) return target == r->data;
    return hasPathSum(r->left, target - r->data) || hasPathSum(r->right, target - r->data);
}

// 8. Print all root-to-leaf paths
void paths(Node* r, vector<int>& cur) {
    if (!r) return;
    cur.push_back(r->data);
    if (!r->left && !r->right) {
        for (size_t i = 0; i < cur.size(); i++) cout << cur[i] << (i + 1 < cur.size() ? "->" : "");
        cout << "\n";
    } else {
        paths(r->left, cur);
        paths(r->right, cur);
    }
    cur.pop_back();                    // backtrack
}

// 9. Lowest Common Ancestor (general binary tree)
Node* lca(Node* r, int a, int b) {
    if (!r) return nullptr;
    if (r->data == a || r->data == b) return r;
    Node* L = lca(r->left, a, b);
    Node* R = lca(r->right, a, b);
    if (L && R) return r;              // a and b are on different sides
    return L ? L : R;
}

// 10. Right-side view (last node of each level)
vector<int> rightView(Node* root) {
    vector<int> res;
    if (!root) return res;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            Node* cur = q.front(); q.pop();
            if (i == n - 1) res.push_back(cur->data);
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }
    return res;
}

void inorder(Node* r) { if (!r) return; inorder(r->left); cout << r->data << " "; inorder(r->right); }

int main() {
    /*
             1
            / \
           2   3
          / \   \
         4   5   6
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);

    cout << "Max depth   : " << maxDepth(root) << "\n";
    cout << "Diameter    : " << diameter(root) << " edges\n";
    cout << "Balanced?   : " << (isBalanced(root) ? "yes" : "no") << "\n";
    cout << "Symmetric?  : " << (isSymmetric(root) ? "yes" : "no") << "\n";
    cout << "Path sum 7? : " << (hasPathSum(root, 7) ? "yes" : "no") << "  (1+2+4)\n";
    cout << "LCA(4,5)    : " << lca(root, 4, 5)->data << "\n";
    cout << "LCA(4,6)    : " << lca(root, 4, 6)->data << "\n";

    cout << "Right view  : ";
    for (int x : rightView(root)) cout << x << " ";
    cout << "\n";

    cout << "All paths:\n";
    vector<int> cur;
    paths(root, cur);

    cout << "Inorder before invert: "; inorder(root); cout << "\n";
    invert(root);
    cout << "Inorder after invert : "; inorder(root); cout << "\n";
    return 0;
}
