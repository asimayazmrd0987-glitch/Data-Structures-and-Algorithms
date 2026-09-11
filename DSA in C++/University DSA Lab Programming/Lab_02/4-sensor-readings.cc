#include <iostream>
using namespace std;

int main() {
    int temperature[6] = {28, 31, 35, 33, 29, 27};
    int highest = temperature[0], above30 = 0;

    // Display + find highest + count in one pass
    cout << "Temperatures: ";
    for (int i = 0; i < 6; i++) {
        cout << temperature[i] << " ";
        if (temperature[i] > highest) highest = temperature[i];
        if (temperature[i] > 30) above30++;
    }
    cout << endl;

    cout << "Highest Temperature = " << highest << endl;
    cout << "Readings above 30 = " << above30 << endl;

    // Same array, accessed via pointer this time
    int *temp = temperature;
    cout << "Via pointer: ";
    for (int i = 0; i < 6; i++) {
        cout << *(temp + i) << " ";
    }
    cout << endl;

    return 0;
}