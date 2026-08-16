#include<iostream>
using namespace std;

int main(){
    
    cout<<"Enter a number: ";

    char a=cin.get();

    if(a>='a' && a<'z'){
        cout <<"Lower Case";
    }

    else if(a>='A' && a<'Z'){
        cout<<"Upper Case";
    }

    else if(a>='0' && a<'9'){
        cout<<"Numeric";
    }
    
    else{
        cout<<"Input is invalid";
    }

    return 0;
}