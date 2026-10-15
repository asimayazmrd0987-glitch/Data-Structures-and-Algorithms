#include <iostream>
using namespace std;

class Queue {
private:
    static const int SIZE = 5;
    int items[SIZE];
    int frontIndex;
    int rearIndex;

public:
    Queue() : frontIndex(-1), rearIndex(-1) {}

    bool isEmpty() const {
        return frontIndex == -1;
    }

    bool isFull() const {
        return rearIndex == SIZE - 1;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full. Cannot add " << value << ".\n";
            return;
        }
        if (isEmpty()) frontIndex = 0;
        items[++rearIndex] = value;
        cout << "Enqueued: " << value << '\n';
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Nothing to remove.\n";
            return;
        }
        cout << "Dequeued: " << items[frontIndex] << '\n';
        if (frontIndex == rearIndex) {
            frontIndex = rearIndex = -1;
        } else {
            ++frontIndex;
        }
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue: EMPTY | FRONT: NONE | REAR: NONE\n";
            return;
        }
        cout << "Queue (front -> rear): ";
        for (int i = frontIndex; i <= rearIndex; ++i) {
            cout << items[i];
            if (i < rearIndex) cout << " -> ";
        }
        cout << "\nFRONT: " << items[frontIndex]
             << " | REAR: " << items[rearIndex] << '\n';
    }
};

int main() {
    Queue q;
    cout << "QUEUE USING ARRAY (capacity = 5)\n";
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout << "Before dequeue:\n";
    q.display();
    q.dequeue();
    cout << "After dequeue:\n";
    q.display();
    return 0;
}
