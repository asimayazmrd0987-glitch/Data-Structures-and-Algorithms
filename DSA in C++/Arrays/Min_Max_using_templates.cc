#include <iostream>
#include <string>
using namespace std;

// Function template for Minimum
template <typename T>
T getMin(T temp[], int n)
{
    T min = temp[0]; // Initialize with first element (works for any type T)
    for (int v = 1; v < n; v++)
    {
        if (temp[v] < min)
        {
            min = temp[v];
        }
    }
    return min;
}

// Function template for Maximum
template <typename T>
T getMax(T temp[], int n)
{
    T max = temp[0]; // Initialize with first element
    for (int v = 1; v < n; v++)
    {
        if (temp[v] > max)
        {
            max = temp[v];
        }
    }
    return max;
}

int main()
{
    int size;
    cout << "Enter the size of array: ";
    cin >> size;

    // Works with integers
    int tempInt[100];
    cout << "Enter " << size << " integers:\n";
    for (int i = 0; i < size; i++)
        cin >> tempInt[i];

    cout << "Int Max: " << getMax(tempInt, size) << endl;
    cout << "Int Min: " << getMin(tempInt, size) << endl;

    // Demonstration with double array (Implicit Template Instantiation)
    double tempDouble[] = {10.5, 3.14, 99.8, 0.45};
    cout << "\nDouble Max: " << getMax(tempDouble, 4) << endl;
    cout << "Double Min: " << getMin(tempDouble, 4) << endl;

    return 0;
}