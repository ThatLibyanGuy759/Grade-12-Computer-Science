#include <iostream>


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

int main() {
    int num1 = 8;
    int num2 = 4;
    
    cout << "GCF of " << num1 << " and " << num2 << " is " << findGCF(num1, num2) << endl;
}