#include <iostream>
#include <vector>
using namespace std;

//  Cubic maximum contiguous subsequence sum algorithm.
int maxSubSum1(const vector<int> &a)
{
    int maxSum = 0;

    for (int i = 0; i < a.size(); ++i)
        for (int j = i; j < a.size(); ++j)
        {
            int thisSum = 0;

            for (int k = i; k <= j; ++k)
                thisSum += a[k];

            if (thisSum > maxSum)
                maxSum = thisSum;
        }

    return maxSum;
}
int main()
{

    vector<int> a = {95, 130, 70, 5};
    cout << "Sum is :" << maxSubSum1(a) << endl;
    return 0;
}