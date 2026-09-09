#include <iostream>
#include <algorithm> 
using namespace std;

int main() {
    int arr[6] = {1, 2, 3, 4, 5, 6};
    int n = 6;

    // Loop through the first half of the array
    for (int i = 0; i < n / 2; i++) {
        // Swap element at index i with element at index (n - 1 - i)
        swap(arr[i], arr[n - 1 - i]);
    }
    // Print the updated array
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}