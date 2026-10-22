#include <iostream>
#include <vector>


using namespace std;

int findGCF(int numOne, int numTwo) {
    numOne = abs(numOne);
    numTwo = abs(numTwo);

    while (numTwo != 0) {
        int temp = numTwo;
        numTwo = numOne % numTwo;
        numOne = temp;
    }
    
    return numOne;
}

int findGCF(int numOne, int numTwo, int numThree) {
    return findGCF(findGCF(numOne, numTwo), numThree);
}

int findGCF(const vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    
    int result = abs(nums[0]);
    for (size_t i = 1; i < nums.size(); i++) {
        result = findGCF(result, nums[i]);
    }
    
    return result;
}

int main() {
    int num1 = 48;
    int num2 = 18;
    
    cout << "GCF of " << num1 << " and " << num2 << " is " << findGCF(num1, num2) << endl;
    cout << "GCF of 48, 18, and 30 is " << findGCF(48, 18, 30) << endl;
    cout << "GCF of {24, 36, 60, 12} is " << findGCF({24, 36, 60, 12}) << endl;
    
    return 0;
}