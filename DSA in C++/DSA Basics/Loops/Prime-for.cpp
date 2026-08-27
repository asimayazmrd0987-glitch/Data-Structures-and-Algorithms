#include <iostream>
using namespace std;

int main()
{
    int j = 5;
    // cout<<"Enter any number :"; cin>>j;
    bool prime = 1;

    for(int i = 2; i<j; i++){

        if (j%i == 0){
            // cout<<j<<" is not a prime num"<<endl;
            prime = 0;
            break;
        }
        
        // else{
        //     cout<<j<<" is a prime number"<<endl;
        // }
        
    }
    if (prime==0){
        cout <<j<<" is not a prime number"<<endl;
    }
    else{
        cout<<j<<" is a prime"<<endl;
    }


    return 0;
}

