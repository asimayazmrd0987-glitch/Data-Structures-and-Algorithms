#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

int main() {
    Node* first = new Node(100);
    Node* second = new Node(200);
    Node* third = new Node(300);

    first->next = second;
    second->next = third;
    third->next = nullptr;

    cout << "Original list: ";
   
    return 0;
}
