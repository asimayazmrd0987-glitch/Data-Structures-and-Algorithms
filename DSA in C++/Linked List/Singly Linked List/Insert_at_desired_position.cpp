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

void display(Node* head) {
     Node* temp = head;

    while(temp != nullptr) {

        cout<<temp->data<<"-> ";
        temp = temp->next;

    }
    cout<<"NULL";
}

// Insert at derires position function
void insertAtdesired(Node*& head, int val) {

    Node* newNode = new Node(val);
    Node* temp = head;

    for(int i=1; i<3 && temp != nullptr; i++ ) {
        temp = temp->next;
    }

    // if (head == nullptr) {
    //     head = newNode;
    //     return;
    // }

    temp->next = newNode;
    newNode = temp->next;    
}

int main() {

    Node* first = new Node(100);
    Node* second = new Node(200);
    Node* third = new Node(300);

    first->next = second;
    second->next = third;
    third->next = nullptr;

    cout<<"Before Insertion :";
    display(first);
    cout<<endl;

    cout<<"After Insertion :";
    insertAtdesired(first, 99);
    display(first);

}
// Before Insertion :100-> 200-> 300-> NULL
// After Insertion :100-> 200-> 300-> 99-> NULL
