#include <iostream>
using namespace std;

// Partition function
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Quick Sort function
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);

        quickSort(arr, low, p - 1);  // Left side
        quickSort(arr, p + 1, high); // Right side
    }
}

int main()
{
    int arr[] = {6, 3, 8, 5, 2, 7, 4};
    int n = 7;
    cout << "Original array: ";
    for (int i=0; i<n; i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}

// Original array: 6 3 8 5 2 7 4 
// Sorted array: 2 3 4 5 6 7 8 