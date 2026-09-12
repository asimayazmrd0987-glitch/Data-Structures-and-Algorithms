#include <iostream>
using namespace std;

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int index;

    cout << "Enter an index: ";
    cin >> index;              // depends on user input — compiler CANNOT know this in advance

    cout << arr[index];        // if index is 10, this compiles fine but crashes/misbehaves at RUNTIME
    return 0;
}