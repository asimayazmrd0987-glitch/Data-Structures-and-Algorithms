#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

struct Queue
{
    int arr[MAX];
    int front, rear;

    Queue() : front(-1), rear(-1) {}

    bool isEmpty() const { return (front == -1) || (front > rear); }
    bool isFull()  const { return rear == MAX - 1; }

    // ---- enqueue: insert at rear ----
    void enqueue(int value)
    {
        if (isFull())
        {
            cout << "  Overflow: queue is full\n";
            return;
        }
        if (front == -1) front = 0;
        arr[++rear] = value;
    }

    // ---- dequeue: remove from front ----
    int dequeue()
    {
        if (isEmpty())
        {
            cout << "  Underflow: queue is empty\n";
            return -1;
        }
        return arr[front++];
    }

    // ---- display: show contents with front and rear marked ----
    void display(const string& label) const
    {
        cout << label;
        if (isEmpty())
        {
            cout << "   [empty]   front = rear = -1\n";
            return;
        }
        cout << "   front -> ";
        for (int i = front; i <= rear; ++i)
        {
            cout << arr[i];
            if (i != rear) cout << " , ";
        }
        cout << "   <- rear    (front = " << front
             << ", rear = " << rear << ")\n";
    }
};

int main()
{
    // Sample request values. Replace with the array given in your lab sheet.
    // Duplicates are intentional: A[0]==A[2] and A[1]==A[7].
    int A[8] = { 7, 3, 7, 1, 9, 4, 2, 3 };
    int X = 5;

    Queue q;
    q.display("Start           :");

    q.enqueue(A[0]);  q.display("1 Enqueue A[0]  :");
    q.enqueue(A[1]);  q.display("2 Enqueue A[1]  :");
    q.enqueue(A[2]);  q.display("3 Enqueue A[2]  :");

    int r1 = q.dequeue();
    q.display("4 Dequeue       :");
    cout << "    (served the oldest request, value " << r1 << ")\n";

    q.enqueue(X);     q.display("5 Enqueue X     :");
    q.enqueue(A[7]);  q.display("6 Enqueue A[7]  :");

    int r2 = q.dequeue();
    q.display("7a Dequeue      :");
    cout << "    (served request value " << r2 << ")\n";

    int r3 = q.dequeue();
    q.display("7b Dequeue      :");
    cout << "    (served request value " << r3 << ")\n";

    return 0;
}