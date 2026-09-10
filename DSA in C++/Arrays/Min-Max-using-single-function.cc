#include <iostream>
#include <climits>
using namespace std;

void getMinMax(int temp[], int n, int &minVal, int &maxVal) {
    minVal = INT_MAX;
    maxVal = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (temp[i] < minVal) minVal = temp[i];
        if (temp[i] > maxVal) maxVal = temp[i];
    }
}

int main() {
    int size;
    cout << "Enter the size of array you want :"; cin >> size;

    int temp[100];
    for (int i = 0; i < size; i++) cin >> temp[i];

    int minVal, maxVal;
    getMinMax(temp, size, minVal, maxVal);   

    cout << "The Maximum value in array is :" << maxVal << endl;
    cout << "The Minimum value in array is :" << minVal << endl;
}