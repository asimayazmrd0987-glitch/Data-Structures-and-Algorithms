/* An Array is a fundamental data structure that stores a fixed-size, sequential collection
of elements of the same data type in contiguous (next-to-each-other) memory locations.*/

#include <iostream>
using namespace std;

int main() {
    int numbers[6] = {10, 20, 30, 40, 50};

    // cout << numbers[0] << endl; // bravo
    // cout << numbers[2] << endl;
    // cout << numbers[4] << endl;
    
    for (int i=0; i<=6; i++){
        cout<<numbers[i]<<endl;
    }

    return 0;
}
// /10
// 20
// 30
// 40
// 50
// 0
// -1606127552