#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {15, 7, 29, 4, 18};

    int maximum = numbers[0];

    for (int i = 1; i < 5; i++) {
        if (numbers[i] > maximum) {
            maximum = numbers[i];
        }
    }

    cout << "Maximum = " << maximum << endl;

    return 0;
}