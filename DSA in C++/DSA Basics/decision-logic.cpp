#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 25, 40, 55, 70};
    int target = 40;
    int index = 2; // --> Inspecting element at index 2

    if (arr[index] == target) {
        cout << "Found target " << target << " at index " << index << endl;
    } else if (arr[index] < target) {
        cout << "Target is larger than " << arr[index] << endl;
    } else {
        cout << "Target is smaller than " << arr[index] << endl;
    }

    return 0;
}