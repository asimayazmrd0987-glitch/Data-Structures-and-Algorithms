#include <iostream>
using namespace std;

int squarebyVal(int a);
void squarebyRef(int &);

int main()
{

    int x{2};
    int z{4};

    cout << "x = " << x << " Before squarebyVal\n ";
    cout << "Value return by squarebyVal : " << squarebyVal(x) << endl;
    cout << "x = " << x << ", After squarebtVal" << endl;

    cout << "z = " << z << " Before squarebyRef\n ";
    squarebyRef(z);
    cout << "z = " << z << ", After squarebtRef" << endl;

    return 0;
}

int squarebyVal(int number)
{
    return number *= number;
}

void squarebyRef(int &numRef)
{
    numRef *= numRef;
}

// x = 2 Before squarebyVal
//  Value return by squarebyVal : 4
// x = 2, After squarebtVal
// z = 4 Before squarebyRef
//  z = 16, After squarebtRef