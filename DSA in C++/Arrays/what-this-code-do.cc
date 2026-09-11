#include <iostream>
#include<array>
using namespace std;

const size_t arraySize{10};
int whatisThis(const array<int, arraySize> &, size_t); // prototype

int main()
{
    array<int, arraySize> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result{whatisThis(a, arraySize)};

    cout<<"Result is "<< result <<endl; // Result is 55

}

int whatisThis(const array<int, arraySize>& b, size_t size) {
    if(size == 1) { //base case lol!
        return b[0];
    }
    else {
        return b[size - 1] + whatisThis(b, size - 1);
    }
}
