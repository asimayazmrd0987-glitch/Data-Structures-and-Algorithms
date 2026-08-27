#include <iostream>
using namespace std;

int main() {
    int numbers[7] = {10, 15, 22, 7, 8, 19, 30};

    int evenCount = 0;
    int oddCount = 0;

    for (int i = 0; i < 7; i++) {
        if (numbers[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    cout << "Even = " << evenCount << endl;
    cout << "Odd = " << oddCount << endl;

    return 0;
}