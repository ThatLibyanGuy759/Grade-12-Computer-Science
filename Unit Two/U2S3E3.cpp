#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter the position in Fibonacci sequence ";
    cin >> num;
    
    if (num  <= 0) {
        cout << "Please enter a positive number." << endl;
        return 1;
    }
    
    if (num == 1 || num == 2) {
        cout << "The " << num << "the Fibonacci number is 1" << endl;
    }
    
    int fib1 = 1, fib2 = 1, fibN;
    for (int i = 3; i <= num; i++) {
        fibN = fib1 + fib2;
        fib1 = fib2;
        fib2 = fibN;
    }
    
    cout << "The " << num << "th Fibonacci number is " << fibN << endl;
}