#include <iostream>
using namespace std;

int main()
{

    char operat;
    cout << "Enter an operator ie(+, -, *, /):";
    cin >> operat;
    while (operat != '*' &&
           operat != '-' &&
           operat != '/' &&
           operat != '+')
    {
        cout << " Invalid Input !" << endl;
        cin >> operat;
    }

    int num1, num2;
    cout << "Enter two intergers to operate them :";
    cin >> num1 >> num2;

    switch (operat)
    {

    case '-':
        cout << "The consequence is :" << num1 - num2 << endl;
        break;
    case '+':
        cout << "The consequence is :" << num1 + num2 << endl;
        break;
    case '*':
        cout << "The consequence is :" << num1 * num2 << endl;
        break;
    case '/':
        cout << "The consequence is :" << num1 / num2 << endl;
        break;
    }
    cout << endl;
}