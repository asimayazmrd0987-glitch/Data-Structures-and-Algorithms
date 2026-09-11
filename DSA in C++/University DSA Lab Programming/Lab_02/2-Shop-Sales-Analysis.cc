#include <iostream>
using namespace std;

int main() {
    int sales[7] = {12, 8, 15, 10, 20, 7, 18};
    int total = 0, highest = sales[0], highestDay = 0, above10 = 0;

    for (int i = 0; i < 7; i++) {
        total += sales[i];                   // running total
        if (sales[i] > highest) {
            highest = sales[i];
            highestDay = i;                   // remember which day
        }
        if (sales[i] > 10) above10++;    // count days over threshold
    }

    cout << "Total Sales = " << total << endl;
    cout << "Highest Sales = " << highest << " (Day " << highestDay + 1 << ")" << endl;
    cout << "Days with sales > 10 = " << above10 << endl;

    return 0;
}