// Merge sort using array[]
#include <iostream>
using namespace std;

void mergeHalves(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) { // Original ascending-order comparison
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
        int mid = left + (right - left) / 2; // 0 + (7 - 0)/2 = 7/2 => 3 and on 3 index there is '3'
        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);
        mergeHalves(arr, temp, left, mid, right);
    }
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 5};
    const int n = sizeof(arr) / sizeof(arr[0]);// sizeof arr => 4x8 = 32 and arr[0]=4 -->32/4 = 8, is the size of array(arr).
    int temp[n];

    cout<< "Before merging: ";
    for (int j=0; j<n; ++j) {
        cout<<arr[j]<<" ";
    }
    cout<<endl;

    mergeSort(arr, temp, 0, n - 1);

    cout << "Original ascending Merge Sort: ";
    for (int value : arr) cout << value << ' ';
    cout << '\n';
    return 0;
}
// Before merging: 38 27 43 3 9 82 10 5 
// Original ascending Merge Sort: 3 5 9 10 27 38 43 82
