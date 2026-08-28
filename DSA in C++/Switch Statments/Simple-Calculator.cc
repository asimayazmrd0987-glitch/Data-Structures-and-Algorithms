#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                cout << "Div by zero!\n";
                return 0;
            }
            return a / b;
        case '^': return pow(a, b);
        default:  return 0;
    }
}

int main() {
    double a, b;
    char op;
    
    cout << "Enter expression (a op b): ";
    cin >> a >> op >> b;
    
    double result = applyOp(a, b, op);
    cout << "Result: " << result << endl;
    return 0;
}