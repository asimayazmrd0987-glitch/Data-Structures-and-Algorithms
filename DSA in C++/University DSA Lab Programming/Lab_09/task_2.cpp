
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

    Node* treeA = nullptr;
    Node* treeB = nullptr;

    int valuesA[] = {10, 20, 30, 40};

    int valuesB[] = {30, 20, 40, 10};

    for (int i = 0; i < 4; i++) {
        treeA = insert(treeA, valuesA[i]);
    }

    for (int i = 0; i < 4; i++) {
        treeB = insert(treeB, valuesB[i]);
    }

    cout << "========== TREE A ==========" << endl;
    cout << "Insertion order: 10, 20, 30, 40"
         << endl << endl;

    showNode(treeA);

    cout << "\n========== TREE B ==========" << endl;
    cout << "Insertion order: 30, 20, 40, 10"
         << endl << endl;

    showNode(treeB);

    deleteTree(treeA);
    deleteTree(treeB);

    return 0;
}
