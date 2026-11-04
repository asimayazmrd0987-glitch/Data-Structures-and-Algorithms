#include <iostream>
#include <vector>
using namespace std;

// Merge two sorted parts: a[l..mid] and a[mid+1..r]
void mergeHalves(vector<int>& a, int l, int mid, int r) {
    vector<int> left(a.begin() + l, a.begin() + mid + 1);
    vector<int> right(a.begin() + mid + 1, a.begin() + r + 1);

    size_t i = 0, j = 0;
    int k = l;                                   // write position in a

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) a[k++] = left[i++];   // <= keeps it stable
        else                     a[k++] = right[j++];
    }
    while (i < left.size())  a[k++] = left[i++]; // leftovers from left
    while (j < right.size()) a[k++] = right[j++]; // leftovers from right
}

void mergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return;                          // base case: 0 or 1 element
    int mid = l + (r - l) / 2;                   // avoids overflow of (l+r)/2
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    mergeHalves(a, l, mid, r);
}

int main() {
    vector<int> a = {38, 27, 43, 3, 9, 82, 10};
    mergeSort(a, 0, (int)a.size() - 1);
    for (int x : a) cout << x << " ";            // 3 9 10 27 38 43 82
    cout << "\n";
}