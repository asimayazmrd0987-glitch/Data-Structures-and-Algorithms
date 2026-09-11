#include <iostream>
using namespace std;

int main() {
    int stock[5] = {20, 15, 30, 10, 25};
    int *asim = stock;   // ptr now holds the address of stock[0] (array name decays to a pointer)

    cout << "Before: ";
    for (int i = 0; i < 5; i++) {
        cout << *(asim + i) << " ";    // *(ptr + i) is identical to stock[i]
    }
    cout << endl;

    // Update every element through the pointer, not the array name
    for (int i = 0; i < 5; i++) {
        *(asim + i) += 5;   // dereference the address, then add 5 to what's stored there
    }

    cout << "After: ";
    for (int i = 0; i < 5; i++) {
        cout << *(asim + i) << " ";
    }
    cout << endl;

    return 0;
}