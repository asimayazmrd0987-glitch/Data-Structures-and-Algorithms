#include <iostream>
using namespace std;

int main() {
    int number;

    cout << "Enter a number: ";
    cin >> number;

    if (number % 2 == 0)
        cout << number << " is Even" << endl;
    else
        cout << number << " is Odd" << endl;

    return 0;
}