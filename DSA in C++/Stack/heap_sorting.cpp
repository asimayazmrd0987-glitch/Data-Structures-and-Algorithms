#include <iostream>
#include <vector>
using namespace std;

// Fix heap property downward from node i
// n = current heap size (not full array size)
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;          // assume root is largest
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    // Is left child larger than current largest?
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Is right child larger than current largest?
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If root wasn't the largest, swap and recurse
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);  // fix the subtree we disrupted
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Phase 1: Build max-heap
    // Start from last non-leaf, go up to root
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Phase 2: Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);   // move current max to end
        heapify(arr, i, 0);     // restore heap on remaining i elements
    }
}

int main() {
    vector<int> arr = {4, 10, 3, 5, 1};

    cout << "Before: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    heapSort(arr);

    cout << "After:  ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    return 0;
}