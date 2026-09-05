#include <iostream>
using namespace std;

int main() {
    int x = 10;

    {
        int y = 20;
        cout << x; 
        cout << y; 
    }

    cout << x; 
    cout << y; 
}

// Scope.cc:14:13: error: 'y' was not declared in this scope
//    14 |     cout << y;
//       |             ^