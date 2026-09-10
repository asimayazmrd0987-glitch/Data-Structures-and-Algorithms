#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

struct Timer
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    ~Timer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "[Execution Time: " << duration << " us / " << duration / 1000.0 << " ms]\n";
    }
};

int findUnique(const vector<int> &arr)
{
    int ans = 0;

    for (int val : arr)
    {
        ans ^= val; // Perform bitwise XOR on every single shit element!
    }

    return ans; // The remaining value is the unique element
}

int main()
{
    Timer t;
    vector<int> arr = {7, 1, 2, 1, 2};

    cout << "Unique element is: " << findUnique(arr) << endl;

    return 0;
}
// Output:
// Unique element is: 7
// [Execution Time: 316 us / 0.316 ms]