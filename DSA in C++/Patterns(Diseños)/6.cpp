#include <iostream>
using namespace std;

int main()
{
    int n = 4;

    int i = 1;
    while (i <= n)
    {
        int j = 1;
        while (j <= i)
        {
            cout << j - i - 1 << " ";
            j++;
        }
        cout << endl;
        i++;
    }

    return 0;
}
// -1 
// -2 -1 
// -3 -2 -1 
// -4 -3 -2 -1 