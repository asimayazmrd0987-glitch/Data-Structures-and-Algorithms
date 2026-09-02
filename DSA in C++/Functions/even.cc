#include <iostream>
using namespace std;

bool iseven(int a)
{

    if (a % 2 == 0)
    {
        cout << "It is even lol!" << endl;
        return true;
    }
    cout<<"Its not even even bro "<<endl;
    return false;
}

int main()
{

    int k{0};
    cout << "Enter a number to check in function :" << endl;
    cin >> k;

    cout << iseven(k) << endl;
}