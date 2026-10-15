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

// Function to reverse the linked list
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    Node* forward = nullptr;

    while (curr != nullptr) {
        forward = curr->next; // 1. Save next node, bcz not to get lost the second and third.
        curr->next = prev;    // 2. Reverse current node's pointer
        prev = curr;          // 3. Move prev one step forward
        curr = forward;       // 4. Move curr one step forward
    }

    return prev; // 'prev' is now the new head of the reversed list
}

// Helper function to print list
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main() {
    // Constructing list: 100 -> 200 -> 300 -> NULL
    Node* first = new Node(100);
    Node* second = new Node(200);
    Node* third = new Node(300);

    first->next = second;
    second->next = third;

    cout << "Original List:  ";
    printList(first);

    // Reverse the list
    Node* newHead = reverseList(first);

    cout << "Reversed List:  ";
    printList(newHead);

    // Clean up memory
    Node* temp = newHead;
    while (temp != nullptr) {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    return 0;
}
// Original List:  100 -> 200 -> 300 -> NULL
// Reversed List:  300 -> 200 -> 100 -> NULL
