#include <iostream>
using namespace std;

int main() {
    int marks[5] = {65, 82, 45, 90, 72};
    int sum = 0, highest = marks[0], passed = 0;

    // Display all marks using for loop
    cout << "Marks are : ";
    for (int i = 0; i < 5; i++) {
        cout << marks[i] << " ";
    }
    cout << endl;

    // Single pass: sum, highest, and pass count together
    for (int i = 0; i < 5; i++) {
        sum += marks[i];                  // running total for average
        if (marks[i] > highest)
            highest = marks[i];  // track max
        if (marks[i] >= 50) 
            passed++;     // count passes
    }

    double average = (double)sum / 5;     // cast to double before dividing, or you lose decimals

    cout << "Average is = " << average << endl;
    cout << "Highest is = " << highest << endl;
    cout << "Passed Students = " << passed << endl;

    return 0;
}