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

class Stack {
private:
    Node* top;

public:

    // Constructor
    Stack() {
        top = nullptr;
    }

    // Push an item onto the stack
    void push(int value) {

        Node* newNode = new Node(value);

        newNode->next = top;
        top = newNode;
    }

    // Pop the top item
    void pop() {

        if (top == nullptr) {
            cout << "Stack Underflow!" << endl;
            return;
        }

        Node* temp = top;

        top = top->next;

        delete temp;
    }

    // Show the top item
    int peek() {

        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return -1;
        }

        return top->data;
    }

    // Display all items from top to bottom
    void display() {

        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return;
        }

        Node* temp = top;

        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    // Count number of items
    int count() {

        int total = 0;
        Node* temp = top;

        while (temp != nullptr) {
            total++;
            temp = temp->next;
        }

        return total;
    }
};

int main() {

    Stack s;

    // Push 5 numbers
    s.push(5);
    s.push(10);
    s.push(15);
    s.push(20);
    s.push(25);

    // Display and count
    cout << "Stack before popping: ";
    s.display();

    cout << "Count: " << s.count() << endl;

    // Pop 2 numbers
    s.pop();
    s.pop();

    // Display and count again
    cout << "\nStack after popping 2 items: ";
    s.display();

    cout << "Count: " << s.count() << endl;

    // Empty the stack
    s.pop();
    s.pop();
    s.pop();

    // Try to pop from empty stack
    s.pop();

    return 0;
}
