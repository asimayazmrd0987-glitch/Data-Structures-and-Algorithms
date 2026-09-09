#include <iostream>
#include <vector>
#include <utility> // Required for std::move
using namespace std;

/**
 * Simple insertion sort.
 */
template <typename Comparable>
void insertionSort(vector<Comparable> &a)
{
    for (size_t p = 1; p < a.size(); ++p)
    {
        Comparable tmp = std::move(a[p]);
        int j;
        for (j = static_cast<int>(p); j > 0 && tmp < a[j - 1]; --j)
        {
            a[j] = std::move(a[j - 1]);
        }
        a[j] = std::move(tmp);
    }
}

int main()
{
    // Sample unsorted vector
    vector<int> data = {34, 8, 64, 51, 32, 21};

    cout << "Before sorting: ";
    for (int val : data)
    {
        cout << val << " ";
    }
    cout << endl;

    // Run insertion sort
    insertionSort(data);

    cout << "After sorting:  ";
    for (int val : data)
    {
        cout << val << " ";
    }
    cout << endl;
return 0;
}