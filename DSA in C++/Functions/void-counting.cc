#include <iostream>
using namespace std;

void printCount(int a)
{

        for (int i = 1; i <= a; i++)
        {
                cout << i << " ";
        }
        cout << endl;
}

int main()
{

        int n = 12;
        printCount(n);
}

// 1 2 3 4 5 6 7 8 9 10 11 12