#include <iostream>
#include <vector>

using namespace std;

class Enemy{
    private: 
        int hp = 20;
        int attackDamage = 10;
        string name = "quinn";
    public:
        int getAttack() const{
            return attackDamage;
        }
        void takeDamage(int damage){
            hp -= damage;
        }
        int getHp() const{
            return hp;
        }
        string getName() const{
            return name;
        }
};

class Player{
    private:
        int hp = 100;
        int attackDamage = 10;
    public:
        int getAttack() const{
            return attackDamage;
        }
        void takeDamage(int damage){
            hp -= damage;
        }
        int getHp() const{
            return hp;
        }
};

int main(){
    vector<Enemy> enemies;
    for (int i = 0; i < 5; i++){
        enemies.push_back(Enemy());
    }

    Player player;
    for (vector<Enemy>::size_type i = 0; i < enemies.size() && player.getHp() > 0; i++){
        Enemy& enemy = enemies[i];
        cout << "\nEnemy " << i + 1 << ": " << enemy.getName() << " has " << enemy.getHp() << " HP and does " << enemy.getAttack() << " damage." << endl;

        while (enemy.getHp() > 0 && player.getHp() > 0){
            enemy.takeDamage(player.getAttack());
            cout << "You deal " << player.getAttack() << " damage. " << enemy.getName() << " has " << enemy.getHp() << " HP left." << endl;

            if (enemy.getHp() <= 0){
                cout << enemy.getName() << " is defeated!" << endl;
                break;
            }

            player.takeDamage(enemy.getAttack());
            cout << enemy.getName() << " attacks for " << enemy.getAttack() << " damage. You have " << player.getHp() << " HP left." << endl;
        }
    }

    if (player.getHp() > 0){
        cout << "\nYou defeated all the enemies and won!" << endl;
    } else{
        cout << "\nThe enemies defeated you. They win!" << endl;
    }
}