#include <iostream>
using namespace std;

int main()
{

    int a = 4;
    int k = 5;

    // AND operator
    cout << " a&k value is :" << (a & k) << endl;

    // OR operator
    cout << " a|k value is :" << (a | k) << endl;

    // NOT operator
    cout << " ~k value is :" << ~k << endl;

    // XOR operator
    cout << " a^k value is :" << (a ^ k) << endl;
}
//*************************************************************************************************************** */
//  a&k value is :4 --> representing in bits ==> 100+101=100(which is 4 in int)                                   *
//  a|k value is :5-->100+101 in OR becomes 101(5).                                                               *
//  ~k value is :-6-->convert all the beginning, then taking 1's complement and 2's complement you will get -6.   *
//  a^k value is :1-->100 xor 101 becomes 1 in xor                                                                *
//  *
//  if you still didn't catch the concept, then 1st learn gates in DLD(digital logic design).                     *
//*************************************************************************************************************** */