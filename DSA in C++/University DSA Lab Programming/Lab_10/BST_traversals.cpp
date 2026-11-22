
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value)
{
    Node* newNode = new Node;

    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

Node* insert(Node* root, int value)
{
    if (root == nullptr)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);

    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

void inOrder(Node* root)
{
    if (root == nullptr)
        return;

    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

void preOrder(Node* root)
{
    if (root == nullptr)
        return;

    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node* root)
{
    if (root == nullptr)
        return;

    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

void levelOrder(Node* root)
{
    if (root == nullptr)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        Node* current = q.front();
        q.pop();

        cout << current->data << " ";

        if (current->left != nullptr)
            q.push(current->left);

        if (current->right != nullptr)
            q.push(current->right);
    }
}

int main()
{
    Node* root = nullptr;

    int values[] = {45, 25, 65, 15, 35, 55, 75};

    for (int i = 0; i < 7; i++)
    {
        root = insert(root, values[i]);
    }

    cout << "In-order: ";
    inOrder(root);

    cout << "\nPre-order: ";
    preOrder(root);

    cout << "\nPost-order: ";
    postOrder(root);

    cout << "\nLevel-order: ";
    levelOrder(root);

    return 0;
}
