#include <iostream>
using namespace std;

class Node
{

public:
    int data;
    Node *next;
};

int main()
{

    Node *a = new Node();
    a->data = 1;
    Node *b = new Node();
    b->data = 2;
    Node *c = new Node();
    c->data = 3;
    c->next = nullptr;
    b->next = c;
    a->next = b;

    cout << a->next->next->data << endl; // 3, Hhaaa!
}