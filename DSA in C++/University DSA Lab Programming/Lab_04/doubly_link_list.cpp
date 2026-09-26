#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *prev;
    Node *next;

    Node(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

int main() {

    Node *node10 = new Node(10);
      Node *node20 = new Node(20);
    Node *node30 = new Node(30);
    Node *node40 = new Node(40);

    node10->next = node20;
      node20->prev = node10;

    node20->next = node30;
    node30->prev = node20;

    node30->next = node40;
    node40->prev = node30;

    Node *head = node10;

       cout << "Doubly Linked List in forward order: ";

    Node *current = head;

    while (current != nullptr) {
        cout << current->data;

        if (current->next != nullptr)
        {
            cout << " ";
        }

        current = current->next;
    }

    cout << endl;

    current = head;

    while (current != nullptr) {
        Node *nextNode = current->next; 
        delete current;                 
        current = nextNode;             
    }

    return 0;
}