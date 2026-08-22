#include <iostream>
using namespace std;

bool mystery(const char *, const char);

int main()
{
    char string1[60], ch;

    cout << "Enter a string :";
    cin >> string1;

    cout << "Enter a character :";
    cin >> ch;

    cout << "The result is :" << mystery(string1, ch) << endl;

    return 0;
}

bool mystery(const char *s1, const char c)
{
    for (; *s1 != '\0'; ++s1)
    {
        if (*s1 == c)
            return true;
    }
    return false;
}