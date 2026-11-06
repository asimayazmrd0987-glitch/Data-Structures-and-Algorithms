// Part 3: Merge Sort an array of strings in alphabetical order.
#include <iostream>
#include <string>
using namespace std;

void mergeHalves(string arr[], string temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) { // Alphabetical ascending order; stable on equality
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int x = left; x <= right; x++) arr[x] = temp[x];
}

void mergeSort(string arr[], string temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);
        mergeHalves(arr, temp, left, mid, right);
    }
}

int main() {
    string names[] = {"zain", "ali", "bilal", "hina", "sara"};
    const int n = sizeof(names) / sizeof(names[0]);
    string temp[n];

    mergeSort(names, temp, 0, n - 1);

    cout << "Names in alphabetical order: ";
    for (const string& name : names) cout << name << ' ';
    cout << '\n';
    return 0;
}
