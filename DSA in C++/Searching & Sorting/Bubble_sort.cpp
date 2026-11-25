#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bubbleSort(int arr[], int n) {
    // Outer loop for each pass
    for (int i = 0; i < n - 1; i++) {
        // Inner loop compares adjacent elements
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the current element is bigger than the next
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, n);

    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}