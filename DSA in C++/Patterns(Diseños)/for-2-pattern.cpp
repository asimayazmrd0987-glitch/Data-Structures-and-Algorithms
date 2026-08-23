#include <iostream>
using namespace std;

int main()
{

    int n = 6;
    for (int i = 1; i <= n; i++) // outer loop for rows
    {

        for (int k = 1; k <= i; k++) // innner loop for columns
        {
            cout << i  ;
        }
        cout << endl;
    }
    return 0;
}
// 1
// 22
// 333
// 4444
// 55555
// 666666