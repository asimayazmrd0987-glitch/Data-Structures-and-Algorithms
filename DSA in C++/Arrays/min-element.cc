#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {15, 7, 29, 4, 18};

    int minimum = numbers[0];

    for (int i = 1; i < 5; i++) {
        if (numbers[i] < minimum) {
            minimum = numbers[i];
        }
    }

    cout << "Minimum = " << minimum << endl;

    return 0;
}