#include <iostream>
using namespace std; 

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail; // Maintaining a tail pointer allows O(1) tail operations

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // O(1) Time Complexity: Insert at the end
    void insertAtTail(int value) {
        DNode* newNode = new DNode(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Forward Traversal
    void traverseForward() const {
        DNode* current = head;
        cout << "Forward:  NULL <-> ";
        while (current != nullptr) {
            cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "NULL\n";
    }

    void traverseBackward() const {
        DNode* current = tail;
        std::cout << "Backward: NULL <-> ";
        while (current != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->prev;
        }
        std::cout << "NULL\n";
    }

    ~DoublyLinkedList() {
        DNode* current = head;
        while (current != nullptr) {
            DNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList dll;
    dll.insertAtTail(10);
    dll.insertAtTail(20);
    dll.insertAtTail(30);
    
    dll.traverseForward();  
    dll.traverseBackward(); 
    return 0;
}

// Forward:  NULL <-> 10 <-> 20 <-> 30 <-> NULL
// Backward: NULL <-> 30 <-> 20 <-> 10 <-> NULL