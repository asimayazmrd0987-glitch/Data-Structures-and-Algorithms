#include <iostream>
using namespace std;

int factorial(int n)
{
    if (n < 0) // this statement is Guard clause for invalid input
        return -1;
    if (n == 0) // base case, This prevents infinite loops. Without a base case, the function continuously
                // allocates new stack frames until the program crashes from a Stack Overflow.
        return 1;

    return n * factorial(n - 1); // Recursive Step, This reduces the problem size with each call, guaranteeing
    //  that n eventually hits 0
}

int main()
{
    int n;
    cout << "Enter a number to get factorial :";
    cin >> n;

    int answer = factorial(n);
    cout << "Factorial of " << n << " is " << answer << endl;
}
/*
1. Enter a number to get factorial :0
Factorial of 0 is 1

2. Enter a number to get factorial :6
Factorial of 6 is 720

*/

/*
Unwinding the recursion when n is 5 (Nesh, Ecomomist)

factorial(0)
= 1

factorial(1) = 1 × 1
= 1

factorial(2) = 2 × 1
= 2

factorial(3) = 3 × 2
= 6

factorial(4) = 4 × 6
= 24

factorial(5) = 5 × 24
= 120
*/