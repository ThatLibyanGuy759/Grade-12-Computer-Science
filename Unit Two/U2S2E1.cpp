#include <vector>

using namespace std;

float returnSum(const vector<float>& nums) {
    float sum = 0.0f;
    for (float num : nums) {
        sum += num;
    }
    return sum;
}

double returnSum(const vector<double>& nums) {
    double sum = 0.0;
    for (double num : nums) {
        sum += num;
    }
    return sum;
}