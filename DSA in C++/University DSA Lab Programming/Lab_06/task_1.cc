
#include <iostream>
using namespace std;

class Queue
{
private:
    int arr[5];
    int front, rear;
    const int SIZE = 5;

public:
    Queue()
    {
        front = -1;// pointing to the first element of the queue
        rear = -1;// pointing to the last element of the queue
    }

    void enqueue(int value)
    {
        if (rear == SIZE - 1)
        {
            cout << "Queue is full!" << endl;
            return;
        }

        if (front == -1)
        {
            front = 0;
        }

        rear++;
        arr[rear] = value;

        cout << value << " inserted." << endl;
    }

    void dequeue()
    {
        if (front == -1)
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        cout << arr[front] << " removed." << endl;

        if (front == rear)
        {
            front = rear = -1;
        }
        else
        {
            front++;
        }
    }

    void display()
    {
        if (front == -1)
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        cout << "Queue: ";

        for (int i = front; i <= rear; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
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
// 10 inserted.
// 20 inserted.
// 30 inserted.
// 10 removed.
// Queue: 20 30
