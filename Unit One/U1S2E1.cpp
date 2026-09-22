#include <iostream>
#include <limits>  
#include <climits>

using namespace std;

int main() {
    int minInt = std::numeric_limits<int>::min();
    int maxInt = std::numeric_limits<int>::max();

    cout << "The lowest possible int value is: " << minInt << "\n";
    cout << "The highest possible int value is: " << maxInt << "\n";
}