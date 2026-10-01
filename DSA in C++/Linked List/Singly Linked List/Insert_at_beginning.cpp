#include<iostream>
using namespace std;

class Node{

    public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }

};

// display function
void display(Node* head) {
     Node* temp = head;

    while(temp != nullptr) {

        cout<<temp->data<<"-> ";
        temp = temp->next;

    }
    cout<<"NULL";
}

// Insert at the beginning function
void insertAtBeginning(Node*& head, int val) {

    Node* veryfirst = new Node(val);

    veryfirst->next = head; //Now 99 points to the old first node
    head = veryfirst;
    
}

int main() {

    Node* first = new Node(100);
    Node* second = new Node(200);
    Node* third = new Node(300);

    first->next = second;
    second->next = third;
    third->next = nullptr;

    insertAtBeginning(first, 99);
    display(first);

}
// 99-> 100-> 200-> 300-> NULL