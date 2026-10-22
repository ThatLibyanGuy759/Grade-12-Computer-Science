#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void printGrid(const vector<vector<char>>& grid) {
    cout << "   ";
    for (int column = 1; column <= grid[0].size(); column++) {
        cout << column << " ";
    }
    cout << endl;

    for (int row = 0; row < grid.size(); row++) {
        cout << row + 1 << "  ";
        for (char cell : grid[row]) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

void selectCell(vector<vector<char>>& grid) {
    int row;
    int column;

    while (true) {
        cout << "Choose a row and column (for example: 2 3): ";
        if (cin >> row >> column) {
            if (row >= 1 && row <= grid.size() &&
                column >= 1 && column <= grid[0].size()) {
                grid[row - 1][column - 1] = 'X';
                break;
            }

            cout << "That location is outside the grid. Try again." << endl;
        } else {
            cout << "Enter two numbers. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
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

    if (!cin || width <= 0 || height <= 0) {
        cout << "Grid width and height must be positive numbers." << endl;
        return 1;
    }

    vector<vector<char>> grid(height, vector<char>(width, '.'));
    printGrid(grid);
    selectCell(grid);
    printGrid(grid);

    usernameConfig(playerOneName,playerTwoName, singlePlayer);
    cout << playerOneName << endl;
    cout << playerTwoName << endl;
}