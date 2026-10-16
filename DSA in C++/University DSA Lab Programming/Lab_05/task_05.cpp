#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Insert a node at the tail of the linked list
void insert(Node*& head, int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Count total nodes in the linked list
int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Traverse and print list elements
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    Node* first = new Node(100);
    Node* second = new Node(200);
    Node* third = new Node(300);

    first->next = second;
    second->next = third;

    cout << "Initial Linked List: ";
    printList(first);

    // Insert 500 at the end
    insert(first, 500);

    cout << "After Inserting 500 at Tail: ";
    printList(first);

    cout << "Total Number of Nodes: " << countNodes(first) << endl;

    // Free dynamic memory
    Node* current = first;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    return 0;
}