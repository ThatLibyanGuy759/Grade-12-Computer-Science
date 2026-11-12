#ifndef U3S4E3_HPP
#include <iostream>
using namespace std;

class Mammal{
    protected:
        int legs = 4;
    public:
        int getLegs(){
            return legs;
        }
};

class Cat: public Mammal{
    public:
        string species = "cat";

        void makeSound(){
            cout << "Meow" << endl;
        }

};

class Human: public Mammal{
    public:
        Human(){
            legs = 2;
        }
} ;

#endif