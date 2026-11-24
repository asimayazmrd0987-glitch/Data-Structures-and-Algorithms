#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    vector<int> output(arr.size());

    for (int x : arr) {
        ++count[x];
    }

    for (int i = 1; i <= maxVal; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; --i) {
        int val = arr[i];
        output[--count[val]] = val;
    }

    arr = move(output);
}

int main() {
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    countingSort(arr);

    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}