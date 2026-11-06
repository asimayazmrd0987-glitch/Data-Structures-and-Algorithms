
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node();

    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

Node* insert(Node* root, int value) {

    if (root == nullptr) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    }

    else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

void showNode(Node* root) {

    if (root == nullptr) {
        return;
    }

    cout << "Node: " << root->data;

    cout << " | Left child: ";

    if (root->left != nullptr) {
        cout << root->left->data;
    }
    else {
        cout << "NULL";
    }

    cout << " | Right child: ";

    if (root->right != nullptr) {
        cout << root->right->data;
    }
    else {
        cout << "NULL";
    }

    cout << endl;

    showNode(root->left);
    showNode(root->right);
}

void deleteTree(Node* root) {

    if (root == nullptr) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

int main() {

    Node* root = nullptr;

    // Quiz marks in the given insertion order
    int marks[] = {45, 25, 65, 15, 35, 55};

    int size = sizeof(marks) / sizeof(marks[0]);

    // Insert marks into BST
    for (int i = 0; i < size; i++) {
        root = insert(root, marks[i]);
    }

    cout << "BINARY SEARCH TREE" << endl;
    cout << "==================" << endl;

    cout << "Node details (Preorder Traversal):"
         << endl << endl;

    // Show every node with its left and right child
    showNode(root);

    // Free allocated memory
    deleteTree(root);

    return 0;
}
