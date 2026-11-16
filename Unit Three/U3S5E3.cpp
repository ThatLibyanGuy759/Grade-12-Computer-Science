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
    while (player.getHp() > 0){
        bool enemiesRemain = false;
        for (vector<Enemy>::size_type i = 0; i < enemies.size(); i++){
            if (enemies[i].getHp() > 0){
                enemiesRemain = true;
                break;
            }
        }
        if (!enemiesRemain){
            break;
        }

        cout << "\nYour turn:" << endl;
        for (vector<Enemy>::size_type i = 0; i < enemies.size(); i++){
            if (enemies[i].getHp() > 0){
                enemies[i].takeDamage(player.getAttack());
                cout << "You deal " << player.getAttack() << " damage to " << enemies[i].getName() << " (Enemy " << i + 1 << "). " << enemies[i].getHp() << " HP left." << endl;
                if (enemies[i].getHp() <= 0){
                    cout << enemies[i].getName() << " (Enemy " << i + 1 << ") is defeated!" << endl;
                }
                break;
            }
        }

        int totalDamage = 0;
        for (vector<Enemy>::size_type i = 0; i < enemies.size(); i++){
            if (enemies[i].getHp() > 0){
                cout << enemies[i].getName() << " (Enemy " << i + 1 << ") attacks for " << enemies[i].getAttack() << " damage." << endl;
                totalDamage += enemies[i].getAttack();
            }
        }
        if (totalDamage > 0){
            player.takeDamage(totalDamage);
            cout << "You take " << totalDamage << " total damage and have " << player.getHp() << " HP left." << endl;
        }
    }

    if (player.getHp() > 0){
        cout << "\nYou defeated all the enemies and won!" << endl;
    } else{
        cout << "\nThe enemies defeated you. They win!" << endl;
    }
}