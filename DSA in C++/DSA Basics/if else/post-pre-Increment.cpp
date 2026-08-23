#include<iostream>
using namespace std;

int main(){
        //post-incrementation demonstration
    unsigned int c{5};
    cout<<"c before postincrement: "<< c<<endl;
    cout<<"postincrementing c :"<< c++ <<endl;
    cout<<"c after increment :"<< c <<endl;
    cout<<endl;

    //pre-incrementation demonstration
    c = 5;
    cout<<"c after pre-increment :"<<c<<endl;
    cout<<"pre-incrementing c :"<<++c<<endl;
    cout<<"c after pre-increment :"<<c<<endl;

}
// c before postincrement: 5
// postincrementing c :5
// c after increment :6

// c after pre-increment :5
// pre-incrementing c :6
// c after pre-increment :6