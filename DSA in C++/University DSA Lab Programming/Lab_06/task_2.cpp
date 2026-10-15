
#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

class Queue
{
private:
    Node* front;
    Node* rear;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(int value)
    {
        Node* newNode = new Node(value);

        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        cout << value << " inserted." << endl;
    }

    void dequeue()
    {
        if (front == nullptr)
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        Node* temp = front;

        cout << temp->data << " removed." << endl;

        front = front->next;

        // If the queue becomes empty
        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
    }

    // Display queue elements
    void display()
    {
        if (front == nullptr)
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        Node* temp = front;

        cout << "Queue: ";

        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    // Free remaining nodes
    ~Queue()
    {
        while (front != nullptr)
        {
            Node* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }
};

int main()
{
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.dequeue();

    q.display();

    return 0;
}
