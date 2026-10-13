#include <vector>

using namespace std;

int returnSum(const vector<int>& nums) {
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    return sum;
}