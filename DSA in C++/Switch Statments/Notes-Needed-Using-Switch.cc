#include <iostream>
using namespace std;

int main()
{

    int amount;
    cout << "Enter the amount you want to break into notes: ";
    cin >> amount;

    int start = 1;
    switch (start)
    {

    case 1:
        cout << "Note 100 :" << amount / 100 << endl;
        amount = amount % 100;
        break;
    case 2:
        cout << "Note 50 :" << amount / 50 << endl;
        amount = amount % 50;
    case 3:
        cout << "Note 20 :" << amount / 20 << endl;
        amount = amount % 20;
    case 4:
        cout << "Note 10 :" << amount / 10 << endl;
        amount = amount / 10;
    }
    return 0;
}

// Enter the amount you want to break into notes: 14510
// Note 100 :145
// Note 50 :0
// Note 20 :0
// Note 10 :1