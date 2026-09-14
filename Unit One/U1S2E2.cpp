#include <iostream>

using namespace std;

int main() {
    double originalDouble = 9.87;
    int convertedInt = originalDouble;  

    cout << "Original double: " << originalDouble << endl;
    cout << "Converted to int: " << convertedInt << endl;
    cout << "Data lost: " << (originalDouble - convertedInt) << endl;

    cout << endl;

    int largeInt = 123456789;
    double convertedDouble = largeInt;
    int backToInt = convertedDouble;

    cout << "Original int: " << largeInt << endl;
    cout << "Converted: " << convertedDouble << endl;
    cout << "Converted back: " << backToInt << endl;
}