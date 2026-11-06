
#include <iostream>
#include <string>
using namespace std;

struct Node {
    int rollNo;
    string name;

    Node* left;
    Node* right;
};

Node* createNode(int rollNo, string name) {

    Node* newNode = new Node();

    newNode->rollNo = rollNo;
    newNode->name = name;

    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

Node* insert(Node* root, int rollNo, string name) {

    if (root == nullptr) {
        return createNode(rollNo, name);
    }

    if (rollNo < root->rollNo) {
        root->left = insert(root->left, rollNo, name);
    }

    else if (rollNo > root->rollNo) {
        root->right = insert(root->right, rollNo, name);
    }

    else {
        cout << "Roll number " << rollNo
             << " already exists" << endl;
    }

    return root;
}

void showNode(Node* root) {

    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }

    cout << "\nROOT NODE" << endl;
    cout << "Roll Number: " << root->rollNo
         << " | Name: " << root->name << endl;

    cout << "\nLEFT CHILD" << endl;

    if (root->left != nullptr) {
        cout << "Roll Number: " << root->left->rollNo
             << " | Name: " << root->left->name << endl;
    }
    else {
        cout << "NULL" << endl;
    }

    cout << "\nRIGHT CHILD" << endl;

    if (root->right != nullptr) {
        cout << "Roll Number: " << root->right->rollNo
             << " | Name: " << root->right->name << endl;
    }
    else {
        cout << "NULL" << endl;
    }
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

    root = insert(root, 50, "Ali");
    root = insert(root, 30, "Sara");
    root = insert(root, 70, "Hamza");
    root = insert(root, 20, "Ayesha");
    root = insert(root, 40, "Bilal");
    root = insert(root, 30, "Zain");

    cout << "\n===== STUDENT RECORDS BST =====" << endl;

    showNode(root);

    // Free allocated memory
    deleteTree(root);

    return 0;
}
