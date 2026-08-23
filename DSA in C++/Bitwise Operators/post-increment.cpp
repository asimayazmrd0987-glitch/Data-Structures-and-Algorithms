#include<iostream>
using namespace std;

int main(){

    int a=2, k=3;
    int post=(a+(k++));

    cout<<post<<endl; // 5, bcz it will use the k first, then will increment it.




}