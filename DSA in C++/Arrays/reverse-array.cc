#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};

    int left = 0;
    int right = 4;

    while (left < right) {
        swap(numbers[left], numbers[right]);

        left++;
        right--;
    }

    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }

    return 0;
}