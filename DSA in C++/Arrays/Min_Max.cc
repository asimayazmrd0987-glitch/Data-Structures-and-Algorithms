#include <iostream>
#include <climits>
using namespace std;

int getMin(int temp[], int n) {
    int min=INT_MAX;
    for(int v=0; v<n; v++){
        if(temp[v]<min){
            min= temp[v];
        }
    }
    return min;
}

int getMax(int temp[], int n) {
    int max=INT_MIN;
    for(int v=0; v<n; v++){
        if(temp[v]>max){
            max= temp[v];
        }
    }
    return max;
}

int main()
{
    int size;
    cout << "Enter the size of array you want :"; cin >> size;

    int temp[100];
    for (int i = 0; i < size; i++) {
        cin >> temp[i];
    }

    cout<< "The Maximum value in array is :"<< getMax(temp, size)<<endl;
    cout<< "The Minimum value in array is :"<< getMin(temp, size)<<endl;
}