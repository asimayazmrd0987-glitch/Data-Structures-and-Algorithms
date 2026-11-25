// 05 - AVL Tree (self-balancing BST)
// Rule: for every node, |height(left) - height(right)| <= 1
// Balance factor (bf) = height(left) - height(right)
// After insert/delete we fix imbalance using rotations -> search/insert/delete are always O(log n).
//
//  Case        Condition                  Fix
//  Left-Left   bf > 1  and bf(left) >= 0  rotate right
//  Left-Right  bf > 1  and bf(left) < 0   rotate left on left child, then rotate right
//  Right-Right bf < -1 and bf(right) <= 0 rotate left
//  Right-Left  bf < -1 and bf(right) > 0  rotate right on right child, then rotate left
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int key;
    int height;            // height of this node (leaf = 1)
    Node *left, *right;
    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int height(Node* n) { return n ? n->height : 0; }
int balanceFactor(Node* n) { return n ? height(n->left) - height(n->right) : 0; }
void updateHeight(Node* n) { n->height = 1 + max(height(n->left), height(n->right)); }

/*
      y                x
     / \              / \
    x   C    --->    A   y
   / \                  / \
  A   B                B   C
*/
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* B = x->right;
    x->right = y;
    y->left = B;
    updateHeight(y);       // y first (it is now lower)
    updateHeight(x);
    return x;              // new root of this subtree
}

/*
    x                    y
   / \                  / \
  A   y      --->      x   C
     / \              / \
    B   C            A   B
*/
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* B = y->left;
    y->left = x;
    x->right = B;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Check balance of node n and fix it if needed
Node* rebalance(Node* n) {
    updateHeight(n);
    int bf = balanceFactor(n);

    if (bf > 1) {                                   // left heavy
        if (balanceFactor(n->left) < 0)             // Left-Right case
            n->left = rotateLeft(n->left);
        return rotateRight(n);                      // Left-Left case
    }
    if (bf < -1) {                                  // right heavy
        if (balanceFactor(n->right) > 0)            // Right-Left case
            n->right = rotateRight(n->right);
        return rotateLeft(n);                       // Right-Right case
    }
    return n;                                       // already balanced
}

Node* insert(Node* n, int key) {
    if (!n) return new Node(key);
    if (key < n->key)      n->left  = insert(n->left, key);
    else if (key > n->key) n->right = insert(n->right, key);
    else return n;                                  // ignore duplicates
    return rebalance(n);
}

Node* minNode(Node* n) { while (n->left) n = n->left; return n; }

Node* remove(Node* n, int key) {
    if (!n) return nullptr;
    if (key < n->key)      n->left  = remove(n->left, key);
    else if (key > n->key) n->right = remove(n->right, key);
    else {
        if (!n->left || !n->right) {                // 0 or 1 child
            Node* child = n->left ? n->left : n->right;
            delete n;
            return child;
        }
        Node* succ = minNode(n->right);             // 2 children
        n->key = succ->key;
        n->right = remove(n->right, succ->key);
    }
    return rebalance(n);
}

bool search(Node* n, int key) {
    if (!n) return false;
    if (key == n->key) return true;
    return key < n->key ? search(n->left, key) : search(n->right, key);
}

void inorder(Node* n)  { if (!n) return; inorder(n->left); cout << n->key << " "; inorder(n->right); }
void preorder(Node* n) { if (!n) return; cout << n->key << " "; preorder(n->left); preorder(n->right); }
void deleteTree(Node* n) { if (!n) return; deleteTree(n->left); deleteTree(n->right); delete n; }

int main() {
    Node* root = nullptr;

    // Sorted input would make a normal BST a linked list. AVL stays balanced.
    for (int k : {10, 20, 30, 40, 50, 25}) root = insert(root, k);

    cout << "Inorder  : "; inorder(root);  cout << "\n";   // sorted
    cout << "Preorder : "; preorder(root); cout << "\n";   // shows the shape (root = 30)
    cout << "Root = " << root->key << ", height = " << root->height << "\n";
    cout << "Search 25: " << (search(root, 25) ? "found" : "not found") << "\n";

    root = remove(root, 40);
    cout << "\nAfter deleting 40\n";
    cout << "Inorder  : "; inorder(root);  cout << "\n";
    cout << "Preorder : "; preorder(root); cout << "\n";

    deleteTree(root);
    return 0;
}
