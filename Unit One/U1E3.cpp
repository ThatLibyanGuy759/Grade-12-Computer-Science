#include <iostream>
#include <cmath>
 
using namespace std;

int main(){
    string animal;
    int year;
    int currentYear = 2026;
    int amountOfAnimals;
    int populationMultiplier;

    cout << "enter a animal" << endl;
    cin >> animal;

    cout << "enter the ammount of animals" << endl;
    cin >> amountOfAnimals;

    cout << "enter the projected year" << endl;
    cin >> year;


    populationMultiplier = year - currentYear;

    cout << "Type of animal:    " << animal << endl;
    cout << "Starting amount:   " << amountOfAnimals << endl;
    cout << "Projecting year:    " << year << endl;
    cout << "Current year:    " << currentYear << endl;
    cout << "Projecting population:    " << amountOfAnimals * pow(2, populationMultiplier) << endl;


}