// 01 - Binary Tree Basics
// A binary tree: every node has at most 2 children (left and right).
#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Insert at the first empty spot, level by level (keeps tree "complete")
Node* insertLevelOrder(Node* root, int val) {
    Node* newNode = new Node(val);
    if (root == nullptr) return newNode;

    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        if (cur->left == nullptr) { cur->left = newNode; break; }
        else q.push(cur->left);
        if (cur->right == nullptr) { cur->right = newNode; break; }
        else q.push(cur->right);
    }
    return root;
}

int countNodes(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int height(Node* root) {            // height measured in nodes
    if (root == nullptr) return 0;
    return 1 + max(height(root->left), height(root->right));
}

int sumNodes(Node* root) {
    if (root == nullptr) return 0;
    return root->data + sumNodes(root->left) + sumNodes(root->right);
}

int countLeaves(Node* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int findMax(Node* root) {
    if (root == nullptr) return INT_MIN;
    return max(root->data, max(findMax(root->left), findMax(root->right)));
}

bool search(Node* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;
    return search(root->left, key) || search(root->right, key);
}

void deleteTree(Node* root) {       // free memory (post-order)
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    /*
      Way 1: build manually
             1
            / \
           2   3
    */
    Node* a = new Node(1);
    a->left = new Node(2);
    a->right = new Node(3);

    // Way 2: build using level-order insert
    Node* root = nullptr;
    for (int v : {1, 2, 3, 4, 5, 6, 7}) root = insertLevelOrder(root, v);

    cout << "Nodes   : " << countNodes(root) << "\n";
    cout << "Height  : " << height(root) << "\n";
    cout << "Sum     : " << sumNodes(root) << "\n";
    cout << "Leaves  : " << countLeaves(root) << "\n";
    cout << "Max     : " << findMax(root) << "\n";
    cout << "Has 5?  : " << (search(root, 5) ? "yes" : "no") << "\n";
    cout << "Has 99? : " << (search(root, 99) ? "yes" : "no") << "\n";

    deleteTree(a);
    deleteTree(root);
    return 0;
}
