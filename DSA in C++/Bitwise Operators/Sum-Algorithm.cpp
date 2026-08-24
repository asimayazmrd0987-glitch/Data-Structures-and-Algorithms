#include <iostream>
using namespace std;

int sum(int n)
{

    int partialSum;
    partialSum = 0;
    for (int i = 1; i <= n; i++)
        partialSum += i * i * i;
    return partialSum;
}

int main()
{

    cout << "Sum is :" << sum(3) << endl; // Iteration 3 (i = 3): 
    // partialSum = 9 + (3 * 3 * 3)--> partialSum = 9 + 27 --> partialSum becomes 36.

    return 0;
}
