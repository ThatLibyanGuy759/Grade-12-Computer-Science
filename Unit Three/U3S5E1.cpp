#include <iostream>
#include <vector>

using namespace std;

class Enemy{
    private: 
        int hp = 20;
        double attackDamage = 10.0;
        string name = "quinn";
    public:
        int getAttack(){
            return attackDamage;
        }
        void takeDamage(int damage){
            hp -= damage;
        }
        int getHp(){
            return hp;
        }
        string getName(){
            return name;
        }
};

int main(){
    vector<Enemy> enemies;
    for (int i = 0; i < 5; i++){
        cout << "adding an enemy to the list" << endl;
        enemies.push_back(Enemy());
    }
    for (int i = 0; i < enemies.size(); i++){
        cout << i << ". " << enemies[i].getName() << " has " << enemies[i].getHp() << " HP and does " << enemies[i].getAttack() << " damage" << endl;
    }
    
}