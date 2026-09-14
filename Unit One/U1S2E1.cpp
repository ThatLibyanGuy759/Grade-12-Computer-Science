#include <iostream>
#include <string>

using namespace std;

int main() {
    string name;
    char letter;
    unsigned short age;
    string phoneNumber;

    
    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter a letter: ";
    cin >> letter;

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter your phone number: ";
    cin >> phoneNumber;

    cout << "Name: " << name << endl;
    cout << "letter: " << letter << endl;
    cout << "Age: " << age << endl;
    cout << "Phone: " << phoneNumber << endl;

}