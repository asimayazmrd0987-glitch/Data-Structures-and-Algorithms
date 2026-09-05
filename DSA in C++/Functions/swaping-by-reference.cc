#include <iostream>
using namespace std;

int swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
    return 0;
}

int main()
{

    int a = 10;
    int b = 20;
    swap(a, b);
    cout << "a :" << a << " b :" << b;
    return 0;
}
// a :20 b :10