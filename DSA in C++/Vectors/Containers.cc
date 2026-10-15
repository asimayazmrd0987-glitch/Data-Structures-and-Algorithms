#include <iostream>
#include <vector>
using namespace std;

// void display(){
//     cout<< "Russia";
// }

int main()
{
    vector<int> numbers = {10, 20, 30, 40, 50};

    // cout << numbers[0] << endl;  // 10
    // cout << numbers[2] << endl;  // 30

    for (int i=0; i<5; i++) {

        cout<<numbers[i]<< " ";
        // display();

    }
    numbers.push_back(60);       // Add an element

    cout << numbers.back() << endl; // 60
    // display();

    return 0;
}