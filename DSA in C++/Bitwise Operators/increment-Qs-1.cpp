#include <iostream>
using namespace std;

int main()
{

    int a = 1;
    int b = 2;

    if (a-- > 0 && ++b > 2)
    {
        cout << "I am in" << endl;
    }
    else
    {
        cout << "I am out" << endl;
    }

    cout << a << " <==> " << b << endl;
}