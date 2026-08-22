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
            cout << i + j - 1 << " ";
            j++;
        }
        cout << endl;
        i++;
    }

    return 0;
}
// output
// 1 
// 2 3 
// 3 4 5 
// 4 5 6 7 