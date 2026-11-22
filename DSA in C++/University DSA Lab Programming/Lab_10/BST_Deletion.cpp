
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

Node* findMin(Node* root)
{
    while (root->left != nullptr)
    {
        root = root->left;
    }

    return root;
}

Node* deleteNode(Node* root, int value)
{
    if (root == nullptr)
        return root;

    if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }

    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }

    else
    {
        if (root->left == nullptr &&
            root->right == nullptr)
        {
            delete root;
            return nullptr;
        }

        else if (root->left == nullptr)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        else if (root->right == nullptr)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        else
        {
            Node* temp = findMin(root->right);

            root->data = temp->data;

            root->right = deleteNode(root->right,
                                     temp->data);
        }
    }

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

    root = deleteNode(root, 15);

    cout << "After deleting 15: ";
    inOrder(root);

    root = deleteNode(root, 25);

    cout << "\nAfter deleting 25: ";
    inOrder(root);

    root = deleteNode(root, 45);

    cout << "\nAfter deleting 45: ";
    inOrder(root);

    cout << "\nFinal Level-order: ";
    levelOrder(root);

    cout << endl;

    return 0;
}
