#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of rows: ";
    cin >> n;

    int i = 1;

    while (i <= n)
    {
        int j = 1;
        while (j <= n - i)
        {
            cout << " ";
            j++;
        }

        int k = 1;
        while (k <= 2 * i - 1)
        {
            cout << " * ";
            k++;
        }

        cout << endl;
        i++;
    }

    i = n - 1;

    while (i >= 1)
    {

        int j = 1;
        while (j <= n - i)
        {
            cout << " ";
            j++;
        }

        int k = 1;
        while (k <= 2 * i - 1)
        {
            cout << " * ";
            k++;
        }

        cout << endl;
        i--;
    }

    return 0;
}
// pattern :
// Enter number of rows: 5
//      * 
//     *  *  * 
//    *  *  *  *  * 
//   *  *  *  *  *  *  * 
//  *  *  *  *  *  *  *  *  * 
//   *  *  *  *  *  *  * 
//    *  *  *  *  * 
//     *  *  * 
//      * 

// Haa! it might be lookin like a drone!