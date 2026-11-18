#ifndef GAMEREMPLATE_HPP
#define GAMEREMPLATE_HPP
#include <iostream>
using namespace std;

class Player{
    private:
        int maxHealth = 20;
        int currentHealth = maxHealth;
        int attackDamage = 10;
        int defense = 5;
        int healingItems = 5;
        int healingAmount = 5;
        int speed = 2;
        string name = "John Doe";
    public:
        int getMaxHealth() const{
            return maxHealth;
        }
        int getCurrentHealth() const{
            return currentHealth;
        }
        int getAttackDamage() const{
            return attackDamage;
        }
        int getDefense() const{
            return defense;
        }
        int getHealingItems() const{
            return healingItems;
        }

        void takeDamage(int damage){
            currentHealth -= damage;
            if (currentHealth < 0){
                currentHealth = 0;
            }
        }
        
        bool useHealingItem() {
            if (healingItems == 0 || currentHealth == maxHealth) {
                return false;
            }

            healingItems--;
            currentHealth += healingAmount;

            if (currentHealth > maxHealth) {
                currentHealth = maxHealth;
            }

            return true;
        }

        string getName() const{
            return name;
        }

        void showHealthBar() const {
            int totalBars = getMaxHealth(); 
            int filledBars = getCurrentHealth() * totalBars / getMaxHealth();

            cout << getName() << "'s Health: [";
            for (int i = 0; i < filledBars; i++) {
                cout << "=";
            }
            for (int i = filledBars; i < totalBars; i++) {
                cout << "-";
            }
            cout << "] " << getCurrentHealth() << " HP" << endl;
        }


        Player(){};
        
};

class Enemy{
    private:
        int maxHealth = 20;
        int currentHealth = maxHealth;
        int attackDamage = 10;
        int defense = 5;
        string name = "Bad Joe";
    public:
        int getMaxHealth() const{
            return maxHealth;
        }
        int getCurrentHealth() const{
            return currentHealth;
        }
        int getAttackDamage() const{
            return attackDamage;
        }
        int getDefense() const{
            return defense;
        }
        string getName() const{
            return name;
        }

        void takeDamage(int damage){
            currentHealth -= damage;
            if (currentHealth < 0){
                currentHealth = 0;
            }
        }

        void showHealthBar() const {
            int totalBars = getMaxHealth(); 
            int filledBars = getCurrentHealth() * totalBars / getMaxHealth();

            cout << getName() << "'s Health: [";
            for (int i = 0; i < filledBars; i++) {
                cout << "=";
            }
            for (int i = filledBars; i < totalBars; i++) {
                cout << "-";
            }
            cout << "] " << getCurrentHealth() << " HP" << endl;
        }

        
        Enemy(){};
        
};



#endif