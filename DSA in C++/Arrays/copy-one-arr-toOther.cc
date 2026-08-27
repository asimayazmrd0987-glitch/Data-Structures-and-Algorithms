#include <iostream>
using namespace std;

int main() {
    int original[5] = {1, 2, 3, 4, 5};
    int copied[5];

    for (int i = 0; i < 5; i++) {
        copied[i] = original[i];
    }

    for (int i = 0; i < 5; i++) {
        cout << copied[i] << " ";
    }

    return 0;
}