#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;       // Value stored in the node
    Node* next;     // Pointer to the next node

    // Constructor
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Linked List class
class LinkedList {
private:
    Node* head;

public:
    // Constructor
    LinkedList() {
        head = nullptr;
    }

    // Destructor
    // This automatically frees memory when object is destroyed
    ~LinkedList() {
        Node* current = head;

        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Add node at the end
    void append(int value) {
        Node* newNode = new Node(value);

        // If list is empty
        if (head == nullptr) {
            head = newNode;
            return;
        }

        // Go to last node
        Node* temp = head;

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        // Connect last node to new node
        temp->next = newNode;
    }

    // Add node at the beginning
    void prepend(int value) {
        Node* newNode = new Node(value);

        // New node points to old head
        newNode->next = head;

        // Head now points to new node
        head = newNode;
    }

    // Insert node at a given position
    // Position 1 means first node
    void insertAt(int value, int position) {
        // If position is 1 or less, insert at beginning
        if (position <= 1) {
            prepend(value);
            return;
        }

        Node* temp = head;

        // Move to node before required position
        for (int i = 1; i < position - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }

        // If position is beyond length, append at end
        if (temp == nullptr) {
            append(value);
            return;
        }

        Node* newNode = new Node(value);

        // Connect new node
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Delete node by value
    bool deleteValue(int value) {
        // If list is empty
        if (head == nullptr) {
            return false;
        }

        // If head node contains the value
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        // Search for the node before the node to delete
        Node* current = head;

        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }

        // If value not found
        if (current->next == nullptr) {
            return false;
        }

        // current->next is the node to delete
        Node* nodeToDelete = current->next;

        // Skip the node
        current->next = nodeToDelete->next;

        // Delete node
        delete nodeToDelete;

        return true;
    }

    // Search for a value
    bool search(int value) {
        Node* temp = head;

        while (temp != nullptr) {
            if (temp->data == value) {
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    // Count number of nodes
    int length() {
        int count = 0;
        Node* temp = head;

        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }

        return count;
    }

    // Print list
    void print() {
        Node* temp = head;

        cout << "HEAD";

        while (temp != nullptr) {
            cout << " -> " << temp->data;
            temp = temp->next;
        }

        cout << " -> NULL" << endl;
    }

    // Reverse linked list
    void reverse() {
        Node* previous = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;

        while (current != nullptr) {
            // Store next node
            nextNode = current->next;

            // Reverse current node's pointer
            current->next = previous;

            // Move pointers one step forward
            previous = current;
            current = nextNode;
        }

        // Previous becomes new head
        head = previous;
    }
};

int main() {
    LinkedList list;

    // Add nodes at the end
    list.append(10);
    list.append(20);
    list.append(30);

    cout << "After append(10, 20, 30):" << endl;
    list.print();

    // Add node at beginning
    list.prepend(5);

    cout << "After prepend(5):" << endl;
    list.print();

    // Insert 15 at position 3
    list.insertAt(15, 3);

    cout << "After insertAt(15, position 3):" << endl;
    list.print();

    // Delete value 20
    list.deleteValue(20);

    cout << "After deleteValue(20):" << endl;
    list.print();

    // Length
    cout << "Length: " << list.length() << endl;

    // Search
    if (list.search(30)) {
        cout << "30 found" << endl;
    } else {
        cout << "30 not found" << endl;
    }

    // Reverse
    list.reverse();

    cout << "After reverse:" << endl;
    list.print();

    return 0;
}
// After append(10, 20, 30):
// HEAD -> 10 -> 20 -> 30 -> NULL
// After prepend(5):
// HEAD -> 5 -> 10 -> 20 -> 30 -> NULL
// After insertAt(15, position 3):
// HEAD -> 5 -> 10 -> 15 -> 20 -> 30 -> NULL
// After deleteValue(20):
// HEAD -> 5 -> 10 -> 15 -> 30 -> NULL
// Length: 4
// 30 found
// After reverse:
// HEAD -> 30 -> 15 -> 10 -> 5 -> NULL