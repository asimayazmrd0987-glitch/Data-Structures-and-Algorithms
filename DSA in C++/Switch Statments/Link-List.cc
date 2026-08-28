#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = nullptr;

void insertEnd() {
    int val;
    cout << "Enter value: ";
    cin >> val;
    Node* newNode = new Node{val, nullptr};
    
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    cout << val << " inserted.\n";
}

void deleteBeg() {
    if (!head) {
        cout << "List empty!\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    cout << temp->data << " deleted.\n";
    delete temp;
}

void display() {
    if (!head) {
        cout << "List empty!\n";
        return;
    }
    Node* temp = head;
    cout << "List: ";
    while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n=== LINKED LIST ===\n";
        cout << "1. Insert at End\n2. Delete from Beginning\n3. Display\n4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertEnd();   break;
            case 2: deleteBeg();   break;
            case 3: display();     break;
            case 4: return 0;
            default: cout << "Invalid!\n";
        }
    }
}