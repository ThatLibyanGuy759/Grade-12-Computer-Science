#include <iostream>

using namespace std;

void printNumbers(int num) {
    if (num > 50) {
        return;
    }
    cout << num << endl;
    printNumbers(num + 1);
}

int main() {
    printNumbers(1);
}