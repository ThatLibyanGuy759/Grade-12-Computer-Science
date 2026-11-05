#include <iostream>

using namespace std;

class Student{
    public:
    string name;
    int grade;
    int studentNumber;
};

int main(){
    Student studentOne = {"Alhadi Ghenniwa", 11, 362730269};
    cout << studentOne.name << endl;
    cout << studentOne.grade << endl;
    cout << studentOne.studentNumber << endl;
}