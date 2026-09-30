#include<iostream>
using namespace std;

class Node {
    public:
    int data;
    Node* next;

    //constructor
    Node(int val) { 
        data = val;
        next = nullptr;
    }
};

int main() {
 
    Node* node1 = new Node(10);
    Node* node2 = new Node(20);
    Node* node3 = new Node(30);

    node1->next = node2;
    node2->next = node3;

    Node* temp = node1;
    cout<<"Link List :";

    // Traversal
    while(temp!= nullptr) {
        cout<<temp->data<<" ";
        temp = temp->next++;
    }

    // Giving freedom to the memory
    Node* current = node1;
    while(current!= nullptr) {

        Node* cut = current->next;
        delete current;
        current = cut;
    }
    

    return 0;


}
// 10 20 30 