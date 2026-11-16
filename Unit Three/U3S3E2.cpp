#include <iostream>

using namespace std;

class Enemy{
    private:
        double hp = 50.0;
        double attackDamage = 10.0;
    public:
        double& getEnemyHp(){
            return hp;
        }
        double getAttackDamage(){
            return attackDamage;
        }


};

class Player{
    private:
        double hp = 20.0;
        double attackDamage = 25.0;
    public:
        Player(double hp, double attackDamage) : hp(hp), attackDamage(attackDamage) {}

        double& getPlayeryHp(){
            return hp;
        }
        double getAttackDamage(){
            return attackDamage;
        }

    Player(){};
};


int main(){
    Player playerOne;
    Enemy enemy;
    string input;
    
    cout << "Youve encountered an enemy! what do you do? \n Attack \n Pass" << endl;
    cin >> input;
    if(input == "Attack"){
        enemy.getEnemyHp() -= playerOne.getAttackDamage();
        cout << "You did " << playerOne.getAttackDamage() << " Damage!" << endl;
        cout << "Enemy is at " << enemy.getEnemyHp() << " HP";
    } else{
        cout << "skipped turn" << endl;
    }

    playerOne.getPlayeryHp() -= enemy.getAttackDamage();
    cout << "Enemy attacks!! -" << enemy.getAttackDamage() << "HP!" << endl;
    cout << "Your at " << playerOne.getPlayeryHp() << "HP!" << endl;
}