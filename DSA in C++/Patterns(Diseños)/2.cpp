#include <iostream>
using namespace std;

int main()
{
    int rows = 0;
    cout << "Enter the number of rows :";
    cin >> rows;

    int i = 0;

    while (i < rows)
    {
        int j = 0;
        while (j < rows)
        {
            cout << i+1<<" ";
            j++;
        }
        cout << endl;
        i++;
    }
    return 0;
}
// output :
// Enter the number of rows :4
// 1 1 1 1 
// 2 2 2 2 
// 3 3 3 3 
// 4 4 4 4 


