#include <iostream>
#include <string>
using namespace std;

int main() {
    string name, department;
    int age;

    cout << "Enter name: ";
    getline(cin, name);           

    cout << "Enter age: ";
    cin >> age;
    cin.ignore();                  

    cout << "Enter department: ";
    getline(cin, department);

    cout << "Name       : " << name << endl;
    cout << "Age        : " << age << endl;
    cout << "Department : " << department << endl;
    return 0;
}