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
    cout << "Sum is :" << maxSubSum1(a) << endl; // Sum is :300
    return 0;
}

/* Convince yourself that this algorithm works (this should not take much convincing).
The running time is O(N3) and is entirely due to lines 13 and 14, which consist of an O(1)
statement buried inside three nested for loops. The loop at line 8 is of size N.
The second loop has size N − i, which could be small but could also be of size N. We
must assume the worst, with the knowledge that this could make the final bound a bit
high. The third loop has size j − i + 1, which again we must assume is of size N. The total
is O(1 · N · N · N) = O(N3). Line 6 takes only O(1) total, and lines 16 and 17 take only
O(N2) total, since they are easy expressions inside only two loops.
*/