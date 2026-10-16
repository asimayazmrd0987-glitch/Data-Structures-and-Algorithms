
#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main()
{
    const int n = 5;
    int original[n], bubble[n], selection[n];

    cout << "Enter 5 numbers: ";
    for (int i = 0; i < n; i++)
    {
        cin >> original[i];
        bubble[i] = original[i];
        selection[i] = original[i];
    }

    bubbleSort(bubble, n);
    selectionSort(selection, n);

    cout << "Bubble Sort: ";
    for (int i = 0; i < n; i++)
        cout << bubble[i] << " ";

    cout << "\nSelection Sort: ";
    for (int i = 0; i < n; i++)
        cout << selection[i] << " ";

    cout << endl;
    return 0;
}
