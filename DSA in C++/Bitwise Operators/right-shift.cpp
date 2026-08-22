#include <iostream>
using namespace std;

int main()
{

    int k = 12;

    cout << (k >> 1) << endl;
    /* here 12(1100 in bits) when move 1 bit to the right
     side becomes 110 in bits, which is 6 in integer.  */

    return 0;
}