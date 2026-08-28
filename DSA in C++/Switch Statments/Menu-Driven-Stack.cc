#include <iostream>
using namespace std;

#define MAX 100

int stack[MAX];
int top = -1;

void push() {
    if (top >= MAX - 1) {
        cout << "Stack Overflow!\n";
        return;
    }
    int val;
    cout << "Enter value: ";
    cin >> val;
    stack[++top] = val;
    cout << val << " pushed.\n";
}

void pop() {
    if (top < 0) {
        cout << "Stack Underflow!\n";
        return;
    }
    cout << stack[top--] << " popped.\n";
}

void peek() {
    if (top < 0) {
        cout << "Stack is empty!\n";
        return;
    }
    cout << "Top: " << stack[top] << endl;
}

void display() {
    if (top < 0) {
        cout << "Stack is empty!\n";
        return;
    }
    cout << "Stack: ";
    for (int i = top; i >= 0; i--)
        cout << stack[i] << " ";
    cout << endl;
}

int main() {
    int choice;
    while (true) {
        cout << "\n=== STACK MENU ===\n";
        cout << "1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: push();    break;
            case 2: pop();     break;
            case 3: peek();    break;
            case 4: display(); break;
            case 5: cout << "Bye!\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}