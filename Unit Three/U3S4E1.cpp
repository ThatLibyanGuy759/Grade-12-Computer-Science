#include <iostream>
using namespace std;

class Mammal{
    public:
        int legs = 4;
        int eyes = 2;
        bool isWarmBlooded = true;
        bool isVertebrate = true;  
};

class Cat: public Mammal{
    public:
        string species = "cat";

        void makeSound(){
            cout << "Meow" << endl;
        }

};


int main(){
    Cat garfield;
    garfield.makeSound();
    cout << "Garfield has " << garfield.legs << " legs" << endl;

}