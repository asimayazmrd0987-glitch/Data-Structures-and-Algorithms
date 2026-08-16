#include<iostream>
using namespace std;

int main(){
    int a=3;
    int b=a+1;
    if((a=4)==b){
        cout<<"Equal";
    } 
    else{
        cout<<"Are not equal";
    }

    return 0;
}