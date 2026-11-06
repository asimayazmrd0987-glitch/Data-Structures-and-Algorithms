// Part 4: Compare Merge Sort counts for sorted and reversed input arrays.
// This uses the same descending-order comparison (>=) as Parts 1 and 2.
#include <iostream>
using namespace std;

int comparisons = 0;

void mergeHalves(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        comparisons++;
        if (arr[i] >= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int x = left; x <= right; x++) arr[x] = temp[x];
}

void mergeSort(int arr[], int temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);
        mergeHalves(arr, temp, left, mid, right);
    }
}

void runTest(const char* label, const int input[], int n) {
    int arr[8];
    int temp[8];

    for (int i = 0; i < n; i++) arr[i] = input[i];

    comparisons = 0; // Reset before each independent test.
    mergeSort(arr, temp, 0, n - 1);

    cout << label << "\nSorted descending: ";
    for (int i = 0; i < n; i++) cout << arr[i] << ' ';
    cout << "\nComparisons: " << comparisons << "\n\n";
}

int main() {
    const int sorted[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    const int reversed[8] = {8, 7, 6, 5, 4, 3, 2, 1};

    runTest("Already sorted input (ascending):", sorted, 8);
    runTest("Reversed input (descending):", reversed, 8);

    return 0;
}
