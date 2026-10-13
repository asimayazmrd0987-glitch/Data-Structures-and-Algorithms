#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;                       // '(' lands here, so it never gets popped by an operator
}

string infixToPostfix(const string& infix) {
    stack<char> st;
    string postfix = "";

    for (char ch : infix) {
        if (isalnum(ch)) {                       // rule 1: operand
            postfix += ch;
        } else if (ch == '(') {                  // rule 2
            st.push(ch);
        } else if (ch == ')') {                  // rule 3
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop();                            // discard the '('
        } else {                                 // rule 4: operator
            while (!st.empty() && precedence(st.top()) >= precedence(ch)) {
                postfix += st.top();
                st.pop();
            }
            st.push(ch);
        }
    }
    while (!st.empty()) {                        // rule 5: flush the stack
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

int main() {
    cout << infixToPostfix("a+b*c+(d*e+f)*g") << endl;   // abc*+de*f+g*+
    cout << infixToPostfix("6523+8*+3+*") << endl; 
    cout << infixToPostfix("1+2*3+(4*5+6)*7") << endl; 
    return 0;
}
// abc*+de*f+g*+
// 65238*+3+*+
// 123*+45*6+7*+