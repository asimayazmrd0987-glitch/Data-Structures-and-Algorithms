#include <iostream>
#include <iomanip>
#include <array>
#include <ctime>
#include <random>
using namespace std;

int main()
{

    default_random_engine engine(static_cast<unsigned int>(time(0)));
    uniform_int_distribution<unsigned int> randomInt(1, 6);

    const size_t arraySize{7};
    array<unsigned int, arraySize> frequency{};
    for (unsigned int roll{1}; roll <= 60000000; roll++) {
        ++frequency[randomInt(engine)];
    }

    cout << "Face" << setw(13) << "Frequency" << endl;

    for (size_t face{1}; face < frequency.size(); face++) {
        cout << setw(4) << face << setw(13) << frequency[face] << endl;
    }
}
/*
Face    Frequency
   1      9998017
   2      9999080
   3     10001451
   4     10002612
   5      9997845
   6     10000995
*/