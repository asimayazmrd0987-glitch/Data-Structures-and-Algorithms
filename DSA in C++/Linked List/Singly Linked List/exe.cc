#include<iostream>
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

int countNodes(Node* first) {
    
    int count =0;
    Node* temp = first;
    while(temp!= nullptr) {
    count++;
    temp = temp->next;
        
}
    
    return count;
}

int main() {

Node* first = new Node(100);
Node* second = new Node(200);
Node* third = new Node(300);

first->next = second;
second->next = third;
third->next = NULL;

Node* temp = first;
while(temp!= nullptr) {
    cout<<temp->data<<" ";
    temp = temp->next;
}
cout<<endl;

int count = countNodes(first);
cout<<"Number of nodes: "<<count<<endl;

return 0;

}
// 100 200 300 
// Number of nodes: 3
// Time Complexity is O(n)