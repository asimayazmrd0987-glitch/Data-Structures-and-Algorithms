#include <iostream>
using namespace std;

int main()
{
    int arr[6] = {56, 73, 34, 57, 53, 75};
    int n = 5;
    for (int i = n; i >=0 ; i--)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}