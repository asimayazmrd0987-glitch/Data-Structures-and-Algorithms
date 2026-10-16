
#include <iostream>
using namespace std;

int main()
{
    int marks[5] = {75, 92, 68, 85, 80};

    for (int i = 0; i < 4; i++)
    {
        int maxIndex = i;

        for (int j = i + 1; j < 5; j++)
        {
            if (marks[j] > marks[maxIndex])
            {
                maxIndex = j;
            }
        }

        int temp = marks[i];
        marks[i] = marks[maxIndex];
        marks[maxIndex] = temp;
    }

    cout << "Marks from highest to lowest: ";

    for (int i = 0; i < 5; i++)
    {
        cout << marks[i] << " ";
    }

    cout << endl;

    return 0;
}
