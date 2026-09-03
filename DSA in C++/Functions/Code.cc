#include <iostream>
#include <string>
using namespace std;

// 1. int — answers "how many / what value"
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;   // MUST return an int — compiler enforces this
}

// 2. bool — answers a yes/no question
bool isEven(int n) {
    return n % 2 == 0;   // the expression itself is already true/false lol!
}

// 3. void — does something, returns nothing
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    // no return statement needed — or just "return;" with nothing after it
}

// 4. char — returns a single character
char getFirstLetter(string name) {
    return name[0];
}

// 5. string — returns text
string reverseString(string s) {
    string result = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        result += s[i];
    }
    return result;
}

int main() {
    int arr[] = {3, 7, 2, 9, 4};

    cout << "Max: " << findMax(arr, 5) << endl;         // uses int return
    cout << "Is 7 even? " << isEven(7) << endl;          // uses bool return (prints 0/1)
    printArray(arr, 5);                                  // uses void — nothing to store
    cout << "First letter: " << getFirstLetter("Asim") << endl;
    cout << "Reversed: " << reverseString("hello") << endl;

    return 0;
}

// Max: 9
// Is 7 even? 0
// 3 7 2 9 4 
// First letter: A
// Reversed: olleh