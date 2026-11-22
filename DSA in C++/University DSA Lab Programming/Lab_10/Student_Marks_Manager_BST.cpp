
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int marks;
    Node* left;
    Node* right;
};

// Create a new node
Node* createNode(int value)
{
    Node* newNode = new Node;

    newNode->marks = value;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

// Insert marks into BST
Node* insert(Node* root, int value)
{
    if (root == nullptr)
        return createNode(value);

    if (value < root->marks)
        root->left = insert(root->left, value);

    else if (value > root->marks)
        root->right = insert(root->right, value);

    return root;
}

// Job 1: In-order traversal
void inOrder(Node* root)
{
    if (root == nullptr)
        return;

    inOrder(root->left);
    cout << root->marks << " ";
    inOrder(root->right);
}

// Job 2: Level-order traversal
void levelOrder(Node* root)
{
    if (root == nullptr)
    {
        cout << "Tree is empty!";
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        Node* current = q.front();
        q.pop();

        cout << current->marks << " ";

        if (current->left != nullptr)
            q.push(current->left);

        if (current->right != nullptr)
            q.push(current->right);
    }
}

// Pre-order traversal
void preOrder(Node* root)
{
    if (root == nullptr)
        return;

    cout << root->marks << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Job 3: Create a copy of the tree
Node* copyTree(Node* root)
{
    if (root == nullptr)
        return nullptr;

    Node* newNode = createNode(root->marks);

    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    return newNode;
}

// Find smallest node
Node* findMin(Node* root)
{
    while (root->left != nullptr)
        root = root->left;

    return root;
}

// Job 4: Delete marks from BST
Node* deleteNode(Node* root, int value)
{
    if (root == nullptr)
        return nullptr;

    if (value < root->marks)
        root->left = deleteNode(root->left, value);

    else if (value > root->marks)
        root->right = deleteNode(root->right, value);

    else
    {
        // Case 1: No children
        if (root->left == nullptr &&
            root->right == nullptr)
        {
            delete root;
            return nullptr;
        }

        // Case 2: Only right child
        else if (root->left == nullptr)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // Case 2: Only left child
        else if (root->right == nullptr)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Two children
        else
        {
            Node* temp = findMin(root->right);

            root->marks = temp->marks;

            root->right = deleteNode(root->right,
                                     temp->marks);
        }
    }

    return root;
}

// Job 5: Free entire tree
void freeTree(Node* root)
{
    if (root == nullptr)
        return;

    freeTree(root->left);
    freeTree(root->right);

    delete root;
}

int main()
{
    Node* root = nullptr;
    Node* copiedTree = nullptr;

    // Insert 10 different student marks
    int marks[] = {75, 45, 90, 30, 60,
                   85, 95, 20, 50, 65};

    for (int i = 0; i < 10; i++)
    {
        root = insert(root, marks[i]);
    }

    int choice, value;

    do
    {
        cout << "\n\n===== STUDENT MARKS MANAGER =====\n";
        cout << "1. Show marks (Lowest to Highest)\n";
        cout << "2. Show marks (Level by Level)\n";
        cout << "3. Save a copy of BST\n";
        cout << "4. Delete student marks\n";
        cout << "5. Free the whole tree\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "\nMarks in ascending order: ";
                inOrder(root);
                break;

            case 2:
                cout << "\nMarks level by level: ";
                levelOrder(root);
                break;

            case 3:
                freeTree(copiedTree);

                copiedTree = copyTree(root);

                cout << "\nTree copied successfully!";
                cout << "\nCopy (Pre-order): ";
                preOrder(copiedTree);
                break;

            case 4:
                cout << "\nEnter marks to delete: ";
                cin >> value;

                if (root == nullptr)
                {
                    cout << "Tree is empty!";
                    break;
                }

                root = deleteNode(root, value);

                cout << "\nUpdated marks: ";
                inOrder(root);
                break;

            case 5:
                freeTree(root);
                root = nullptr;

                freeTree(copiedTree);
                copiedTree = nullptr;

                cout << "\nMemory freed successfully!";
                break;

            case 6:
                cout << "\nExiting program...";

                freeTree(root);
                freeTree(copiedTree);
                root = nullptr;
                copiedTree = nullptr;
                break;

            default:
                cout << "\nInvalid choice!";
        }

    } while (choice != 6);

    return 0;
}
