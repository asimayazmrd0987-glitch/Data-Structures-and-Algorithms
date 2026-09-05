#include <iostream>
using namespace std;

int main() {
    float price, total;
    int quantity;

    cout << "Enter item price: ";
    cin >> price;
    cout << "Enter quantity: ";
    cin >> quantity;

    total = price * quantity;

    cout << "Total bill: " << total << endl;
    return 0;
}