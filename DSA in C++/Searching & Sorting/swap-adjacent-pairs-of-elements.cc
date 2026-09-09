#include<iostream>
using namespace std;

void SwapArray(int arr[], int size)
{
    for (int i = 0; i < size; i += 2)
    {
        if (i+1 < size)
        {
            swap(arr[i], arr[i + 1]);
        }
    }
}

void viewArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{

    int even[6] = {1, 2, 3, 4, 5, 6};
    int odd[5] = {12, 41, 74, 52, 46};

    SwapArray(even, 6);
    viewArray(even, 6); // Output for even: 2 1 4 3 6 5

    SwapArray(odd, 5);
    viewArray(odd, 5);  // Output for add: 41 12 52 74 46
}

