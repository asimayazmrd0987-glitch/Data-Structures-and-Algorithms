#include <iostream>
using namespace std;

class Node {

    public:
    int data;
    Node* next;
};

int main()
{
    Node *node1 = new Node();
    node1->data = 10;

    Node *node2 = new Node();
    node2->data = 20;
    node2->next = nullptr; // node2 is currently the last node

    node1->next = node2; // THIS is the actual "link" — node1 now points to node2

    // Now walk the chain starting from node1:
    cout << node1->data << endl;       // 10
    cout << node1->next->data << endl; // follow node1's pointer to node2, print ITS data: 20

    return 0;
}

// 10
// 20