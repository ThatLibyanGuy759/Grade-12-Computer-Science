#include <iostream>
#include <string>
#include <cstdio>
using namespace std;


int main(){
    string fullName;
    int seatNum;
    char theaterSection;
    string answer;

    double subtotal = 20.92;
    double tax;
    double total;


    cout << "welcome user, before we book your ticket to Avengers Endgame we need to ask you some information" << endl;
    cout << "What is your full name" << endl;
    getline(cin, fullName);
    cout << "Nice, " << fullName << endl;

    cout << "which section would you like t9o sit in the theater \n A \n B \n C \n D \n Please input one of these letters" << endl;
    cin >> theaterSection;

    while (theaterSection != 'A' && theaterSection != 'B' && theaterSection != 'C' && theaterSection != 'D') {
    
        cout << "Invalid input, try again: ";
        cin >> theaterSection;
    }
    
    cout << "now I need you to select a seat between 1 and 200" << endl;
    cin >> seatNum;

    while(seatNum < 1 || seatNum > 200){
        cout << "invalid input, try again" << endl;
        cin >> seatNum;
    }

    cout << "allat will cost roughly $20.92, do you want your recipt (y/n)?" << endl;

    cin >> answer;

    if(answer == "y"){
        printf("|--------------------------------|\n");
        printf("|Name: %25s |\n", fullName.c_str());
        printf("|Section: %22c |\n", theaterSection);
        printf("|Seat: %25d |\n", seatNum);
        printf("|Price: %24.2f |\n", subtotal);
        printf("|--------------------------------|\n");
    }
    else{
        return false;
    }
}
