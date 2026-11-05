#include "U3S1E3.hpp"

using namespace std;

int main(){
    Student studentOne = {"Alhadi Ghenniwa", 11, 362730269, {'A', 'A', 'B', 'A'}};
    cout << studentOne.name << endl;
    cout << studentOne.grade << endl;
    cout << studentOne.studentNumber << endl;
    cout << "REPORT CARD:" << endl;
    for (const auto& grades : studentOne.marks) {
        cout << grades << endl;
    }
    
}