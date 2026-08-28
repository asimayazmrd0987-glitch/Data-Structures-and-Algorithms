#include <iostream>
#include <stack>
#include <string>
using namespace std;

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default:  return 0;
    }
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

string infixToPostfix(string infix) {
    stack<char> st;
    string result;

    for (char c : infix) {
        if (isalnum(c)) {
            result += c;
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top(); st.pop();
            }
            st.pop(); // pop '('
        }
        else if (isOperator(c)) {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                result += st.top(); st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        result += st.top(); st.pop();
    }
    return result;
}

int main() {
    string expr;
    cout << "Enter infix expression: ";
    cin >> expr;
    cout << "Postfix: " << infixToPostfix(expr) << endl;
    return 0;
}