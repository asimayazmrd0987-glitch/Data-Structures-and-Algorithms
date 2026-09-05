#include <iostream>
using namespace std;

void changeValue(int x)
{
    x = 100;
}

void changeReference(int &x)
{
    x = 200;
}

int main()
{
    int a = 10;

    changeValue(a);
    cout << a << endl;

    changeReference(a);
    cout << a << endl;
    return 0;
}
// 10
// 200