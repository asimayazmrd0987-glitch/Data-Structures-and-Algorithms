#include <iostream>
using namespace std;

int main()
{
    int n=5;
    // cout << "Enter number of rows: ";
    // cin >> n;

    // Upper half
    int i = 1;

    while (i <= n)
    {
        // this loop print spaces
        int j = 1;
        while (j <= n - i)
        {
            cout << "  ";
            j++;
        }

        // here it print stars
        int k = 1;
        while (k <= 2 * i - 1)
        {
            cout << "* ";
            k++;
        }

        cout << endl;
        i++;
    }

    // <== Lower half ==>
    i = n - 1;

    while (i >= 1)
    {
        // Print spaces
        int j = 1;
        while (j <= n - i)
        {
            cout << "  ";
            j++;
        }

        // Print stars
        int k = 1;
        while (k <= 2 * i - 1)
        {
            cout << "* ";
            k++;
        }

        cout << endl;
        i--;
    }

    return 0;
}
// output :
//         * 
//       * * * 
//     * * * * * 
//   * * * * * * * 
// * * * * * * * * * 
//   * * * * * * * 
//     * * * * * 
//       * * * 
//         * 