#include <vector>

using namespace std;

double calculateAverage(const vector<int>& numbers) {
    if (numbers.empty()) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (int num : numbers) {
        sum += num;
    }
    
    return sum / numbers.size();
}

float calculateAverage(const vector<float>& numbers) {
    if (numbers.empty()) {
        return 0.0f;
    }
    
    float sum = 0.0f;
    for (float num : numbers) {
        sum += num;
    }
    
    return sum / numbers.size();
}