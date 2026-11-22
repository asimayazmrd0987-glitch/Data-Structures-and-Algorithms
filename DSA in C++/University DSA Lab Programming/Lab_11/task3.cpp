
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* root)
{
    if (root == nullptr)
        return 0;

    return root->height;
}

int getBalance(Node* root)
{
    if (root == nullptr)
        return 0;

    return getHeight(root->left) - getHeight(root->right);
}

Node* createNode(int key)
{
    Node* newNode = new Node;

    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;

    return newNode;
}

// Right Rotation
Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));

    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));

    return x;
}

// Left Rotation
Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));

    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));

    return y;
}

// AVL Insertion
Node* insert(Node* root, int key)
{
    if (root == nullptr)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);

    else if (key > root->key)
        root->right = insert(root->right, key);

    else
        return root;

    root->height = 1 + max(getHeight(root->left),
                           getHeight(root->right));

    int bf = getBalance(root);

    // LL Case
    if (bf > 1 && key < root->left->key)
        return rightRotate(root);

    // RR Case
    if (bf < -1 && key > root->right->key)
        return leftRotate(root);

    // LR Case
    if (bf > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (bf < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder Traversal
void inorder(Node* root)
{
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

int main()
{
    Node* root = nullptr;

    int n, roll;

    cout << "Enter number of roll numbers: ";
    cin >> n;

    // Take roll numbers from user
    for (int i = 0; i < n; i++)
    {
        cout << "Enter roll number: ";
        cin >> roll;

        root = insert(root, roll);
    }

    // Display root
    if (root != nullptr)
    {
        cout << "\nRoot: " << root->key << endl;

        // Display height
        cout << "Height of AVL Tree: "
             << getHeight(root) << endl;

        // Display inorder
        cout << "Inorder Traversal: ";
        inorder(root);

        cout << endl;
    }

    return 0;
}
