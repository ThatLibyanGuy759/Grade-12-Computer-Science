#include <iostream>
#include <vector>

using namespace std;

void printGrid(int gridWidth, int gridHeight){
    for(int i = 0; i < gridWidth; i++){
        for(int j = 0; j < gridHeight; j++){
            cout << "0 ";
        }
        cout << endl;
    }
}

void playerConfigs(string input, bool singlePlayer){
    cout << "are you playing with a friend(yes or no)" << endl;
    cin >> input;

    if(input == "yes") {
        singlePlayer = false;
    }
    else {
        singlePlayer = true;
    }
}

void usernameConfig(string playerOneName, string playerTwoName, bool isSinglePlayer){
    if(isSinglePlayer == true){
        playerTwoName = "CPU";

        cout << "what is your name" << endl;
        getline(cin, playerOneName);
    }
    else{
        cout << "Player 1 name: " << endl;
        getline(cin, playerOneName);
        cout << "Player 2 name: " << endl;
        getline(cin, playerTwoName);
    }
}
int main() {
    int width;
    int height;
    bool singlePlayer = false;
    string input;
    string playerOneName;
    string playerTwoName;

    playerConfigs(input, singlePlayer);

    cout << "what width do you want your grid?" << endl; 
    cin >> width;
    
    cout << "what height do you want your grid" << endl;
    cin >> height;

    printGrid(width, height);
    usernameConfig(playerOneName,playerTwoName, singlePlayer);
    cout << playerOneName << endl;
    cout << playerTwoName << endl;
}