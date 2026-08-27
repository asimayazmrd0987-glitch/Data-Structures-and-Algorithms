#include <iostream>
using namespace std;

int main() {
    int numbers[6] = {10, 25, 7, 40, 15, 30};
    int target = 40;

    for (int i = 0; i < 6; i++) {
        if (numbers[i] == target) {
            cout << "Found at index: " << i << endl;
            return 0;
        }
    }

    cout << "Not found" << endl;

    return 0;
}
// This is O(n).