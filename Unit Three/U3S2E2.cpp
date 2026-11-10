#include <iostream>

using namespace std;

class Enemy{
    public:
    double hp;
    double attackDamage;
};

class Player{
    public:
    double currentHp;
    double maxHp;
    double attackDamage;
    void showHealthBar() const;
};


void Player::showHealthBar() const {
    int totalBars = maxHp; 
    int filledBars = static_cast<int>((currentHp / 20.0) * totalBars); 

    cout << "Player Health: [";
    for (int i = 0; i < filledBars; i++) {
        cout << "=";
    }
    for (int i = filledBars; i < totalBars; i++) {
        cout << "-";
    }
    cout << "] " << currentHp << " HP" << endl;
}

int main(){
    Player playerOne = {20.0, 20.0, 25.0};
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

    playerOne.currentHp -= enemy.attackDamage;
    cout << "Enemy attacks!! -" << enemy.attackDamage << "HP!" << endl;
    playerOne.showHealthBar();
    cout << "Your at " << playerOne.currentHp << "HP!" << endl;
}