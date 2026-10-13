#include <iostream>

using namespace std;

void printNumbers(int n) {
    if (n > 50) {
        return;
    }
    cout << n << std::endl;
    printNumbers(n + 1);
}

int main() {
    printNumbers(1);
}