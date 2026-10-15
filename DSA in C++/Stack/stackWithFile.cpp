
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int main()
{
    stack<char> st;
    ifstream file("input.txt");

    // checks if the file exists!
    if (!file.is_open())
    {
        cout << "File could not be opened!" << endl;
        return 1;
    }

    char ch;

    // Read characters from the file
    while (file.get(ch))
    {
        st.push(ch);
    }

    file.close();

    // Print characters in reverse order
    cout << "Reversed file content: ";

    while (!st.empty())
    {
        cout << st.top();
        st.pop();
    }

    cout << endl;

    return 0;
}
// Reversed file content: !gnireenignE esreveR
// ZAYA MISA