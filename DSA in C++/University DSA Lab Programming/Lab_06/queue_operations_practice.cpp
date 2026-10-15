#include <iostream>
using namespace std;

class Queue {
private:
    static const int SIZE = 5;
    int items[SIZE];
    int frontIndex = -1;
    int rearIndex = -1;

public:
    bool isEmpty() const { return frontIndex == -1; }
    bool isFull() const { return rearIndex == SIZE - 1; }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Cannot enqueue " << value << ": queue is full.\n";
            return;
        }
        if (isEmpty()) frontIndex = 0;
        items[++rearIndex] = value;
    }

    bool dequeue(int& removedValue) {
        if (isEmpty()) return false;
        removedValue = items[frontIndex];
        if (frontIndex == rearIndex) frontIndex = rearIndex = -1;
        else ++frontIndex;
        return true;
    }

    bool peek(int& frontValue) const {
        if (isEmpty()) return false;
        frontValue = items[frontIndex];
        return true;
    }

    void displayState(const char* operation) const {
        cout << operation << "\n  Queue (front -> rear): ";
        if (isEmpty()) {
            cout << "EMPTY\n  FRONT: NONE | REAR: NONE\n";
            return;
        }
        for (int i = frontIndex; i <= rearIndex; ++i) {
            cout << items[i];
            if (i < rearIndex) cout << " -> ";
        }
        cout << "\n  FRONT: " << items[frontIndex]
             << " | REAR: " << items[rearIndex] << '\n';
    }
};

int main() {
    Queue q;
    int value = 0;
    q.displayState("Start with empty queue:");

    q.enqueue(5);
    q.displayState("1. enqueue(5):");

    q.enqueue(10);
    q.displayState("2. enqueue(10):");

    q.enqueue(15);
    q.displayState("3. enqueue(15):");

    if (q.dequeue(value)) cout << "  Removed value: " << value << '\n';
    q.displayState("4. dequeue():");

    q.enqueue(20);
    q.displayState("5. enqueue(20):");

    if (q.peek(value)) cout << "  peek() returns: " << value << '\n';
    else cout << "  peek(): queue is empty\n";
    q.displayState("6. peek(): (queue is unchanged)");

    return 0;
}
