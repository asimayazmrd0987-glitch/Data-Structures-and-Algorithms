#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

int main()
{
    Node *node10 = new Node(10);
    Node *node20 = new Node(20);
    Node *node30 = new Node(30);

    node10->next = node20;
    node20->next = node30;

    node30->next = node10;

    Node *head = node10;

    cout << "Circular Linked List printed exactly once: ";

    if (head != nullptr)
    {
        Node *temp = head;

        do
        {
            cout << temp->data;

            temp = temp->next;

            if (temp != head)
            {
                cout << " ";
            }

        } while (temp != head);
    }

    cout << endl;

    if (head != nullptr)
    {
        Node *temp = head->next;

        while (temp != head)
        {
            Node *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        delete head;
    }

    return 0;
}