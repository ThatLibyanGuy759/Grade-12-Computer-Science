#include<iostream>
#include<string>

using namespace std;

int main(){
    string input;
    string word;

    cout << "Please enter a word: ";
    getline(cin, input);
    word = input;

    if (word.length() == 5){
        cout << "this is 5 letters long";
    } else {
        cout << "this is NOT 5 letter long";
    }

}