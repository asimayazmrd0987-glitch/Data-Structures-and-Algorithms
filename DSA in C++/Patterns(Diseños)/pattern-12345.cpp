#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of row in interger :";
    cin >> n;

    int i = 1;
    int count=1;
    while (i <= n)
    {
        int j = 1;
        while (j <= n)
        {
            cout << count << " ";
            count=count+1;
            j++;
        }
        cout<<endl;
        i++;
    }
    return 0;
}
// output :
// Enter number of row in interger :4
// 1 2 3 4 
// 5 6 7 8 
// 9 10 11 12 
// 13 14 15 16 