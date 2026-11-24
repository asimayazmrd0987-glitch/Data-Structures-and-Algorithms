#include <iostream>
using namespace std;

// Restore the Max Heap property
void heapify(int arr[], int n, int i)
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check whether left child is larger!!
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    // Check whether right child is larger
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    // If a child is larger, swap and continue
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

// Heap Sort
void heapSort(int arr[], int n)
{
    // Phase 1: Build Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // Phase 2: Extract elements
    for (int i = n - 1; i > 0; i--)
    {
        // Move largest element to the end
        swap(arr[0], arr[i]);

        // Restore heap, excluding sorted elements
        heapify(arr, i, 0);
    }
}

int main()
{
    int arr[] = {4, 10, 3, 5, 1};

    int n = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, n);

    cout << "Sorted Array: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}
// Sorted Array: 1 3 4 5 10 