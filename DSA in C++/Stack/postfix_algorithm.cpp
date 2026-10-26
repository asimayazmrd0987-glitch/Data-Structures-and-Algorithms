#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

int evaluatePostfix(const string& expr) {
    stack<int> s;
    stringstream ss(expr);
    string token;
    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            s.push(stoi(token));
        } else {
            int b = s.top(); s.pop();   // right operand lol
            int a = s.top(); s.pop();   // left operand
            if (token == "+") s.push(a + b);
            else if (token == "-") s.push(a - b);
            else if (token == "*") s.push(a * b);
            else if (token == "/") s.push(a / b);
        }
    }
    return s.top();
}

int main() {
    cout << evaluatePostfix("5 6 2 + * 12 4 / -");  // 37
}