#include <iostream>

using namespace std;

class Enemy{
    public:
    double hp;
    double attackDamage;
};

class Player{
    public:
    double hp;
    double attackDamage;
};


int main(){
    Player playerOne = {20.0, 25.0};
    Enemy enemy = {50.0, 10.0};
    string input;
    
    cout << "Youve encountered an enemy! what do you do? \n Attack \n Pass" << endl;
    cin >> input;
    if(input == "Attack"){
        enemy.hp -= playerOne.attackDamage;
        cout << "You did " << playerOne.attackDamage << " Damage!" << endl;
        cout << "Enemy is at " << enemy.hp << " HP";
    } else{
        cout << "skipped turn" << endl;
    }

    playerOne.hp -= enemy.attackDamage;
    cout << "Enemy attacks!! -" << enemy.attackDamage << "HP!" << endl;
    cout << "Your at " << playerOne.hp << "HP!" << endl;
}