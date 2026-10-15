#include <iostream>
using namespace std;

class Queue {
private:
    struct Node {
        int data;
        Node* next;
        explicit Node(int value) : data(value), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    ~Queue() {
        while (frontNode != nullptr) {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
        rearNode = nullptr;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        cout << "Enqueued: " << value << '\n';
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Nothing to remove.\n";
            return;
        }
        Node* temp = frontNode;
        cout << "Dequeued: " << temp->data << '\n';
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue: EMPTY | FRONT: NONE | REAR: NONE\n";
            return;
        }
        cout << "Queue (front -> rear): ";
        for (Node* current = frontNode; current != nullptr; current = current->next) {
            cout << current->data;
            if (current->next != nullptr) cout << " -> ";
        }
        cout << "\nFRONT: " << frontNode->data
             << " | REAR: " << rearNode->data << '\n';
    }
};

int main() {
    Queue q;
    cout << "QUEUE USING LINKED LIST\n";
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
