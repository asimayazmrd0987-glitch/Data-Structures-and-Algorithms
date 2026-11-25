#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Inorder: Left -> Root -> Right
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Level Order (BFS): Level by level using a queue
void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

int main() {
    /* Tree structure:
          1
         / \
        2   3
       / \
      4   5
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Inorder: ";
    inorder(root);      // Output: 4 2 5 1 3
    cout << "\nLevel Order: ";
    levelOrder(root);   // Output: 1 2 3 4 5
    return 0;
}
// Inorder: 4 2 5 1 3 
// Level Order: 1 2 3 4 5 
