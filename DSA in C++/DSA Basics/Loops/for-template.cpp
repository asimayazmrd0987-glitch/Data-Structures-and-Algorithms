#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename Comparable>
const Comparable &findMax(const vector<Comparable> &a)
{
    if (a.empty())
        throw runtime_error("Vector is empty");

    size_t maxIndex = 0;

    for (size_t i = 1; i < a.size(); ++i)
    {
        if (a[maxIndex] < a[i])
            maxIndex = i;
    }

      return a[maxIndex];
}

int main()
{
    vector<int> numbers = {10, 4, 25, 7, 18};

    cout << findMax(numbers) << endl;

return 0;
}
