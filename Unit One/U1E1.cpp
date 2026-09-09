#include <iostream>
using namespace std;


int main(){
    string fullName;
    int seatNum;
    char theaterSection;

    double subtotal;
    double tax;
    double total;


    cout << "welcome user, before we book your ticket to Avengers Endgame we need to ask you some information" << endl;
    cout << "What is your full name" << endl;
    getline(cin, fullName);
    cout << "Nice, " << fullName << endl;

    cout << "which section would you like t9o sit in the theater \n A \n B \n C \n D \n Please input one of these letters" << endl;
    cin >> theaterSection;
    cout << "you inputed " << theaterSection;

    cout << "now I need you to select a seat between 1 and 200" << endl;
    cin >> seatNum;

    while(seatNum < 1 || seatNum > 200){
        cout << "invalid input, try again" << endl;
        cin >> seatNum;
    }

    cout << "you chose " << seatNum;

    cout << "allat will cost roughly $938290.92, is that fine with you?" << endl;

    cin;

    cout << "it dont matter"; 
}
