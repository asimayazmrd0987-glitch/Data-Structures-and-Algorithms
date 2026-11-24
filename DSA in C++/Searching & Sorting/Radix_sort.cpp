#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countingSortByDigit(vector<int>& arr, int exp) {
    int n = static_cast<int>(arr.size());
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; ++i) {
        ++count[(arr[i] / exp) % 10];
    }

    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        int digit = (arr[i] / exp) % 10;
        output[--count[digit]] = arr[i];
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
    }
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(arr);

    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}