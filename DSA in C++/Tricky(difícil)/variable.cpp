#include <iostream> 
using namespace std;

// What will be the value of variable y after this code executes?
int main() {
int x = 0;
int y = 10;
if (x != 0 && ++y > 10) {
    // Do nothing
}
cout << y;
}