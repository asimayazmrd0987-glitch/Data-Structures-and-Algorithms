#include <iostream>
using namespace std;

void printd(int arr[], int t) {
    for (int i = 0; i < t; i++)
    {
        cout << arr[i] << " ";
    }
    int bar = sizeof(bar)/sizeof(int);
    cout<<endl;
    cout<<"Size of bar is :"<<bar<<endl;
    cout<<endl;
}

int main()
{
    int arr[12];
    for (int i = 1 - 1; i < 11; i++) {
        arr[i] = 1;
        cout << arr[i]<<" ";
    }
    cout << endl;

    int bar[7]={1,2};
    printd(bar, 11);


    int size = sizeof(arr)/sizeof(int);
    cout<<"Size of arr is :"<<size<<endl;

    return 0;
}

