#include<iostream>
using namespace std;

int main(){
    int amount;
    cout << "Enter the amount you want to break into notes: "; 
    cin >> amount;

    // 1. Calculate 100s
    int notes100 = amount / 100;    // Find how many 100s fit
    amount = amount % 100;          // Update amount to just the remainder

    // 2. Calculate 50s with the leftover amount
    int notes50 = amount / 50;
    amount = amount % 50;

    // 3. Calculate 20s with the leftover amount
    int notes20 = amount / 20;
    amount = amount % 20;

    // 4. Calculate 10s with the leftover amount
    int notes10 = amount / 10;
    amount = amount % 10;

    // Print the final breakdown
    cout << "100 Notes: " << notes100 << endl;
    cout << " 50 Notes: " << notes50 << endl;
    cout << " 20 Notes: " << notes20 << endl;
    cout << " 10 Notes: " << notes10 << endl;

    return 0;
}