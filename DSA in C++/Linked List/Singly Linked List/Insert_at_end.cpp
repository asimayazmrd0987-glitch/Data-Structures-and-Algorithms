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

void insert(Node*& head, int value) {
    Node* newNode = new Node(value);

    // If list is empty, update the actual head pointer
    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) { // Move until the last node
        temp = temp->next;
    }
    temp->next = newNode; // Connect the new node at the end
}

// Helper function to print list
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
    third->next = nullptr;

    cout << "Original list: ";
    printList(first);

    // Insert 500 at the end
    insert(first, 500);

    cout << "After insertion: ";
    printList(first); 

    // Freedom to memory!
    Node* current = first;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    return 0;
}
// Original list: 100 200 300 
// After insertion: 100 200 300 500 