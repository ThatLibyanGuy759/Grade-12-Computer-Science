#include <iostream>

using namespace std;

class Student{
    private:
        string name = "Alhadi Ghenniwa";
        int grade = 11;
        int studentNumber = 362730269;

    public:
        string getStudentName(){
            return name;
        }
        int getGrade(){
            return grade;
        }
        int getStudentNumber(){
            return studentNumber;
        }

    Student(){};
};

int main(){
    Student studentOne;
    cout << studentOne.getStudentName() << endl;
    cout << studentOne.getGrade() << endl;
    cout << studentOne.getStudentNumber() << endl;
}