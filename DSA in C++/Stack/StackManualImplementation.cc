#include<iostream>
using namespace std;

class Stack{
    public:
    int *arr;
    int top;
    int size;

    Stack(int size){
    this->size = size;
    top = -1;
    arr = new int[size];
}

void push(int element){
    if (size-top>1) {
        top++;
        arr[top] = element; }
    else {
        cout<<"stack overflow bro! " <<endl;
    }
    
}

void pop(){
    if(top>=0)
        top--;
    else
        cout<<"Cannot pop lol!";
    
}

int peek(){
    if (top>=0 && top<size)
        return arr[top];
    else 
        cout<<"Stack empty!"<<endl;
        return -1;
}

bool porEmpty(){
    if(top == -1)
        return true;
    else
        return false;
}

};

int main() {
    Stack s(5);;;
    s.push(1); 
    s.push(2);
    s.push(3);
    s.push(90);
    s.push(63);
    s.push(68);

    s.pop();
    cout<<s.peek()<<endl;

    s.pop();
    cout<<s.peek()<<endl;

    s.pop();
    cout<<s.peek()<<endl;

    s.pop();
    cout<<s.peek()<<endl;

    s.pop();
    cout<<s.peek()<<endl;


}
/* stack overflow bro! 
90
3
2
1
Stack empty!
-1
*/