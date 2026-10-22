#include <iostream>
using namespace std;
#include <vector>

// Function to perform insertion sort on a vector
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    // Start from the second element (index 1) as the first element is already "sorted"
    for (int i = 1; i < n; ++i) {
        int key = arr[i]; // The element currently being positioned
        int j = i - 1;

        // Shift elements of arr[0..i-1] that are greater than the key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // Insert the key into its correct sorted position
        arr[j + 1] = key;
    }
}

void printVector(const std::vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    vector<int> data = {9, 5, 1, 4, 3};
    
    cout << "Original array: ";
    printVector(data);

    insertionSort(data);

    cout << "Sorted array:   ";
    printVector(data);

    return 0;
}
