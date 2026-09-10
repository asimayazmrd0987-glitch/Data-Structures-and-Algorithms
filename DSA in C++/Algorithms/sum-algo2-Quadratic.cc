#include <iostream>
#include <vector>
using namespace std;
// Quadratic maximum contiguous subsequence sum algorithm.

int maxSubSum2(const vector<int> &a)
{
    int maxSum = 0;

    for (int i = 0; i < a.size(); ++i)
    {
        int thisSum = 0;
        for (int j = i; j < a.size(); ++j)
        {
            thisSum += a[j];

            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}

int main()
{
    vector<int> a = {78, 5, 2};
    cout << "Sum is :" << maxSubSum2(a) << endl; // Sum is :85
    return 0;
}

/*We can avoid the cubic running time by removing a for loop. This is not always possible, but in this case 
there are an awful lot of unnecessary computations present in the
algorithm. The inefficiency that the improved algorithm corrects can be seen by noticing
that j
k=i Ak = Aj + j−1
k=i Ak, so the computation at lines 13 and 14 in algorithm 1 is
unduly expensive. Figure 2.6 shows an improved algorithm. Algorithm 2 is clearly O(N2);
the analysis is even simpler than before.
There is a recursive and relatively complicated O(N logN) solution to this problem,
which we now describe. If there didn’t happen to be an O(N) (linear) solution, this would
be an excellent example of the power of recursion. The algorithm uses a “divide-andconquer” strategy.
The idea is to split the problem into two roughly equal subproblems which are then solved recursively. This is the “divide” part. The “conquer” stage consists
of patching together the two solutions of the subproblems, and possibly doing a small
amount of additional work, to arrive at a solution for the whole problem.
In our case, the maximum subsequence sum can be in one of three places. Either it
occurs entirely in the left half of the input, or entirely in the right half, or it crosses the
middle and is in both halves. The first two cases can be solved recursively. The last case
can be obtained by finding the largest sum in the first half that includes the last element
in the first half, and the largest sum in the second half that includes the first element in
the second half. These two sums can then be added together. As an example, consider the
following input:
First Half      |       Second Half
  4  −3     5 −2 −1 2    6 −2
*/