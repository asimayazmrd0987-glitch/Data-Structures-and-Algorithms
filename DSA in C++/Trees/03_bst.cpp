// 03 - Binary Search Tree (BST)
// Rule: left subtree < node < right subtree. Inorder traversal gives sorted order.
// Average time: search/insert/delete = O(log n). Worst case (sorted input) = O(n).
#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->data)      root->left  = insert(root->left, key);
    else if (key > root->data) root->right = insert(root->right, key);
    return root;                       // duplicates are ignored
}

bool search(Node* root, int key) {
    if (!root) return false;
    if (key == root->data) return true;
    return key < root->data ? search(root->left, key) : search(root->right, key);
}

Node* findMin(Node* root) { while (root && root->left)  root = root->left;  return root; }
Node* findMax(Node* root) { while (root && root->right) root = root->right; return root; }

Node* remove(Node* root, int key) {
    if (!root) return nullptr;
    if (key < root->data)      root->left  = remove(root->left, key);
    else if (key > root->data) root->right = remove(root->right, key);
    else {
        // Case 1: no child
        if (!root->left && !root->right) { delete root; return nullptr; }
        // Case 2: one child
        if (!root->left)  { Node* t = root->right; delete root; return t; }
        if (!root->right) { Node* t = root->left;  delete root; return t; }
        // Case 3: two children -> replace with inorder successor (smallest on right)
        Node* succ = findMin(root->right);
        root->data = succ->data;
        root->right = remove(root->right, succ->data);
    }
    return root;
}

void inorder(Node* r) { if (!r) return; inorder(r->left); cout << r->data << " "; inorder(r->right); }

// Check if a tree is a valid BST: every node must stay inside (low, high)
bool isValidBST(Node* root, long long low = LLONG_MIN, long long high = LLONG_MAX) {
    if (!root) return true;
    if (root->data <= low || root->data >= high) return false;
    return isValidBST(root->left, low, root->data) &&
           isValidBST(root->right, root->data, high);
}

// Lowest Common Ancestor in a BST
Node* lca(Node* root, int a, int b) {
    if (!root) return nullptr;
    if (a < root->data && b < root->data) return lca(root->left, a, b);
    if (a > root->data && b > root->data) return lca(root->right, a, b);
    return root;                       // split point = LCA
}

// Kth smallest (1-based) using inorder
void kthHelper(Node* r, int k, int& count, int& ans) {
    if (!r || count >= k) return;
    kthHelper(r->left, k, count, ans);
    if (++count == k) { ans = r->data; return; }
    kthHelper(r->right, k, count, ans);
}
int kthSmallest(Node* root, int k) { int c = 0, ans = -1; kthHelper(root, k, c, ans); return ans; }

void deleteTree(Node* r) { if (!r) return; deleteTree(r->left); deleteTree(r->right); delete r; }

int main() {
    Node* root = nullptr;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) root = insert(root, v);

    cout << "Inorder (sorted): "; inorder(root); cout << "\n";
    cout << "Search 60: " << (search(root, 60) ? "found" : "not found") << "\n";
    cout << "Search 65: " << (search(root, 65) ? "found" : "not found") << "\n";
    cout << "Min: " << findMin(root)->data << "  Max: " << findMax(root)->data << "\n";
    cout << "Valid BST? " << (isValidBST(root) ? "yes" : "no") << "\n";
    cout << "LCA(20, 40): " << lca(root, 20, 40)->data << "\n";
    cout << "LCA(20, 80): " << lca(root, 20, 80)->data << "\n";
    cout << "3rd smallest: " << kthSmallest(root, 3) << "\n";

    root = remove(root, 20);   // leaf
    root = remove(root, 30);   // one child
    root = remove(root, 50);   // two children (root)
    cout << "After deleting 20, 30, 50: "; inorder(root); cout << "\n";

    deleteTree(root);
    return 0;
}
