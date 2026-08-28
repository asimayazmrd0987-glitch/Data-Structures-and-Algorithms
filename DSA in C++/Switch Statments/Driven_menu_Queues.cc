#include <iostream>
using namespace std;

#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

bool isFull() {
    return (rear + 1) % SIZE == front;
}

bool isEmpty() {
    return front == -1;
}

void enqueue() {
    if (isFull()) {
        cout << "Queue is full!\n";
        return;
    }
    int val;
    cout << "Enter value: ";
    cin >> val;
    if (front == -1) front = 0;
    rear = (rear + 1) % SIZE;
    queue[rear] = val;
    cout << val << " enqueued.\n";
}

void dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty!\n";
        return;
    }
    cout << queue[front] << " dequeued.\n";
    if (front == rear) front = rear = -1;
    else front = (front + 1) % SIZE;
}

void displayQueue() {
    if (isEmpty()) {
        cout << "Queue is empty!\n";
        return;
    }
    cout << "Queue: ";
    int i = front;
    while (true) {
        cout << queue[i] << " ";
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    cout << endl;
}

int main() {
    int choice;
    while (true) {
        cout << "\n=== CIRCULAR QUEUE ===\n";
        cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: enqueue();      break;
            case 2: dequeue();      break;
            case 3: displayQueue(); break;
            case 4: return 0;
            default: cout << "Invalid!\n";
        }
    }
}