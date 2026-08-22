#include<iostream>
using namespace std;

int main(){
    int n;
    cout<<"Enter a number :"; cin>>n;
    int i = 2;
    while(i<n){
        if (n%i == 0){
            cout<<n<<" is not a prime number";
        }
        else{
            cout <<n<<" is a prime number";
        }
        i++;
    }
}