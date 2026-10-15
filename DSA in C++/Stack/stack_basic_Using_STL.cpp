#include<iostream>
#include<stack>
using namespace std;

int display(stack<int> s) {
    while(!s.empty()) {
        cout<<s.top()<<" ";
        s.pop();
    }
        return 0;
}



int main() {

    stack<int> s;

    s.push(2); // add element to the stack.
    s.push(56);
    s.push(12);
    s.pop(); // 12 is being removed from stack 

    // display(s);
    // cout<<endl;
    // cout<<s.empty();

    if (s.empty()) {
        cout<<"Stack is empty bro! " <<endl;
    }
    else {
        cout<<"Stack is not empty! " <<endl;
        cout<<"Here they are :";
        display(s);
    }
    
}

