#include <iostream>
#include <string>

using namespace std;

// Custom Array-Based Stack Class for characters
class CharStack {
private:
    char* arr;
    int topIndex;
    int capacity;

public:
    // Constructor
    CharStack(int size = 100) {
        capacity = size;
        arr = new char[capacity];
        topIndex = -1;
    }

    // Destructor to free heap memory
    ~CharStack() {
        delete[] arr;
    }

    // Check if stack is empty
    bool isEmpty() const {
        return topIndex == -1;
    }

    // Check if stack is full
    bool isFull() const {
        return topIndex == capacity - 1;
    }

    // Push character onto stack
    void push(char c) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++topIndex] = c;
    }

    // Pop character from stack
    char pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return '\0';
        }
        return arr[topIndex--];
    }
};

// Function to reverse a word using the custom stack
string reverseWord(const string& word) {
    CharStack stack(word.length());

    // Step 1: Push all characters onto the stack
    for (char c : word) {
        stack.push(c);
    }

    // Step 2: Pop all characters to construct reversed word
    string reversed = "";
    while (!stack.isEmpty()) {
        reversed += stack.pop();
    }

    return reversed;
}

int main() {
    // 3 Test Cases as specified in the requirements
    string testCases[] = {"stack", "level", "lab"};

    for (int i = 0; i < 3; i++) {
        string original = testCases[i];
        string reversed = reverseWord(original);

        cout << "Test Case " << i + 1 << ":" << endl;
        cout << "  Input Word    : " << original << endl;
        cout << "  Reversed Word : " << reversed << endl;
        cout << endl;
    }

    // Interactive User Input Demonstration
    string userWord;
    cout << "\nEnter a student name/word to reverse: ";
    cin >> userWord;

    cout << "Reversed Result: " << reverseWord(userWord) << endl;

    return 0;
}