/*
Problem: Understand how a stack behaves by tracing operations by hand and then checking your answer with code.
Requirements:
1.	Starting with an empty stack, draw the stack (top on the right) after each operation: push(5), push(8), push(2), pop(), push(9), pop(), pop().
2.	Write the same operations in main() of the array stack and run it. Print the top using peek() after each step.
3.	Compare the program output with your hand-drawn answer.
4.	In 2 to 3 lines, explain why a stack is called LIFO and give one real-life example of your own.
Expected Output:
•	A table of stack contents after each operation.
•	Program output matching the table.
•	A short written explanation of LIFO
*/

#include <iostream>
using namespace std;

class Stack {
private:
    int arr[10];
    int top;

public: // Constructor
    Stack() {
        top = -1;
    }

    // Add an element
    void push(int value) {
        if (top == 9) {
            cout << "Stack Overflow!" << endl;
            return;
        }

        arr[++top] = value; // here arr[0] become 5
    }

    // Remove the top element
    void pop() {
        if (top == -1) {
            cout << "Stack Underflow!" << endl;
            return;
        }

        top--;
    }

    // here this function return the top element
    int peek() {
        if (top == -1) {
            return -1;   
        }

        return arr[top];
    }

    // Display stack contents
    void display() {
        if (top == -1) {
            cout << "[]";
            return;
        }

        cout << "[";

        for (int i = 0; i <= top; i++) {
            cout << arr[i];

            if (i < top) {
                cout << ", ";
            }
        }

        cout << "]";
    }
};

int main() {

    Stack s;

    cout << "Start: ";
    s.display();
    cout << "   Top: Empty" << endl;

    s.push(5);
    cout << "push(5): ";
    s.display();
    cout << "   Top: " << s.peek() << endl;

    s.push(8);
    cout << "push(8): ";
    s.display();
    cout << "   Top: " << s.peek() << endl;

    s.push(2);
    cout << "push(2): ";
    s.display();
    cout << "   Top: " << s.peek() << endl;

    s.pop();
    cout << "pop():    ";
    s.display();
    cout << "   Top: " << s.peek() << endl;

    s.push(9);
    cout << "push(9): ";
    s.display();
    cout << "   Top: " << s.peek() << endl;

    s.pop();
    cout << "pop():    ";
    s.display();
    cout << "   Top: " << s.peek() << endl;

    s.pop();
    cout << "pop():    ";
    s.display();
    cout << "   Top: " << s.peek() << endl;

    return 0;
}