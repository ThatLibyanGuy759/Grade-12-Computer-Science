#include <iostream>
#include "GameTemplate.hpp"

using namespace std;

int main(){
    Player player;
    Enemy enemy;
    char choice;

    cout << "A wild " << enemy.getName() << " appears!" << endl;

    while (player.getCurrentHealth() > 0 && enemy.getCurrentHealth() > 0){
        cout << "\n";
        player.showHealthBar();
        enemy.showHealthBar();
        cout << "Choose an action: (a)ttack or (h)eal (" << player.getHealingItems() << " healing items left): ";

        if (!(cin >> choice)){
            cout << "\nBattle ended." << endl;
        }

        if (choice == 'a' || choice == 'A'){
            enemy.takeDamage(player.getAttackDamage());
            cout << "You attack " << enemy.getName() << " for " << player.getAttackDamage() << " damage." << endl;
        } else if (choice == 'h' || choice == 'H'){
            if (!player.useHealingItem()){
                cout << "You cannot heal: you're either at full health or out of items." << endl;
                continue;
            }
            cout << "You use a healing item." << endl;
        } else{
            cout << "Choose 'a' to attack or 'h' to heal." << endl;
            continue;
        }

        if (enemy.getCurrentHealth() == 0){
            cout << enemy.getName() << " is defeated. You win!" << endl;
            break;
        }

        player.takeDamage(enemy.getAttackDamage());
        cout << enemy.getName() << " attacks you for " << enemy.getAttackDamage() << " damage." << endl;

        if (player.getCurrentHealth() == 0){
            cout << "You have been defeated. " << enemy.getName() << " wins!" << endl;
        }
    }
}