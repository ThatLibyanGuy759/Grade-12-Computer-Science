#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;

//structs of all required stuff

struct Cell {
    int row;
    int column;
    char state;
};

struct ShotResult {
    bool hit;
    int adjacentBoats;
};

//making a variable for our grid which is just a vector within a vector with the cells representing the grid
typedef vector<vector<Cell>> Grid;

//basic for loops making our grid row by colum
Grid createGrid(int height, int width) {
    Grid grid(height, vector<Cell>(width));
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = {i, j, '.'};
        }
    }
    return grid;
}

//this prints our actual grid with labels
void displayCellGrid(const Grid& grid) {
    if(grid.empty() || grid[0].empty()) {
        return;
    }

    cout << "   ";
    for(int i = 1; i <= static_cast<int>(grid[0].size()); i++) {
        cout << i << " ";
    }

    cout << endl;

    for(int i = 0; i < static_cast<int>(grid.size()); i++) {
        cout << i + 1 << "  ";
        for (const Cell& cell : grid[i]) {
            cout << cell.state << " ";
        }
        cout << endl;
    }
}

//displays the grid
void displayIntegerGrid(const vector<vector<int>>& grid) {
    for(const vector<int>& row : grid) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

//displays the values
void displayIntegerValues(const vector<int>& values) {
    for(int value : values) {
        cout << value << " ";
    }
    cout << endl;
}

//handles the coordinates
bool readCoordinate(const Grid& grid, const string& prompt, int& row, int& column) {
    while(true) {
        cout << prompt;
        if (!(cin >> row >> column)) {
            if (cin.eof()) {
                return false;
            }

            //if the int value input is invalid we run it back
            cout << "Enter two numbers. try another input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        //checks if the spot the user inputs is actually in the grid
        if(row >= 1 && row <= static_cast<int>(grid.size()) && column >= 1 && column <= static_cast<int>(grid[0].size())) {
            return true;
        }

        //if the inputs is outside the grid and dosent meet the 4 requirements
        cout << "That location is outside the grid. put another input plz" << endl;
    }
}

//sees how many boats are near
int countAdjacentBoats(const Grid& grid, int row, int column, int direction = 0) {

    //offset to see if theres boats 1 spot near by on all sides
    static const int rowOffsets[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int columnOffsets[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    //Stops after checking all eight neighboring squares.
    if(direction == 8) {
        return 0;
    }

    int adjacentRow = row + rowOffsets[direction];
    int adjacentColumn = column + columnOffsets[direction];
    int boatAtPosition = 0;

    //adds one if theres a boat next to it from top, bottom, left, right, diagonally all four ways
    if(adjacentRow >= 0 && adjacentRow < static_cast<int>(grid.size()) && adjacentColumn >= 0 && adjacentColumn < static_cast<int>(grid[0].size()) && grid[adjacentRow][adjacentColumn].state == 'B') {
        boatAtPosition = 1;
    }

    return boatAtPosition + countAdjacentBoats(grid, row, column, direction + 1);
}

//placing boats
void placeBoats(Grid& grid, int boatCount, const string& playerName) {
    cout << playerName << ", place your " << boatCount << " ships by entering a row and column." << endl;

    //checking how many boats there is to place
    for(int i = 1; i <= boatCount;) {
        int row;
        int column;
        cout << "Your grid:" << endl;
        displayCellGrid(grid);

        if(!readCoordinate(grid, "Place ship " + to_string(i) + ": ", row, column)) {
            return;
        }

        //if there already is a boat there, as they cant stack boats
        if(grid[row - 1][column - 1].state != '.') {
            cout << "There is already a ship there." << endl;
        } else{
            grid[row - 1][column - 1].state = 'B';
            i++;
        }
    }
}

void placeCpuBoats(Grid& grid, int boatCount, mt19937& randomGenerator) {
    vector<pair<int, int>> availableSquares;
    for (int row = 0; row < static_cast<int>(grid.size()); row++) {
        for (int column = 0; column < static_cast<int>(grid[row].size()); column++) {
            availableSquares.push_back(make_pair(row, column));
        }
    }

    for (int boat = 0; boat < boatCount; boat++) {
        uniform_int_distribution<int> chooseSquare(
            0, static_cast<int>(availableSquares.size()) - 1);
        int selected = chooseSquare(randomGenerator);
        pair<int, int> square = availableSquares[selected];
        grid[square.first][square.second].state = 'B';
        availableSquares.erase(availableSquares.begin() + selected);
    }
}

//Checks whether any shot positions remain.
bool hasUnfiredSquares(const Grid& shotHistory) {
    for(const vector<Cell>& row : shotHistory) {
        for(const Cell& cell : row) {
            if (cell.state == '.') {
                return true;
            }
        }
    }
    return false;
}

bool chooseCpuShot(const Grid& shotHistory, mt19937& randomGenerator,
                   int& row, int& column) {
    vector<pair<int, int>> availableShots;
    for (int currentRow = 0; currentRow < static_cast<int>(shotHistory.size()); currentRow++) {
        for (int currentColumn = 0;
             currentColumn < static_cast<int>(shotHistory[currentRow].size());
             currentColumn++) {
            if (shotHistory[currentRow][currentColumn].state == '.') {
                availableShots.push_back(make_pair(currentRow, currentColumn));
            }
        }
    }

    if (availableShots.empty()) {
        return false;
    }

    uniform_int_distribution<int> chooseShot(
        0, static_cast<int>(availableShots.size()) - 1);
    pair<int, int> shot = availableShots[chooseShot(randomGenerator)];
    row = shot.first + 1;
    column = shot.second + 1;
    return true;
}

//Reads a valid shot that has not already been taken.
bool readPlayerShot(const string& playerName, const Grid& shotHistory, int& row, int& column) {
    cout << playerName << "'s shots:" << endl;
    displayCellGrid(shotHistory);

    while(true) {
        if(!readCoordinate(shotHistory, "Choose a row and column to fire at: ", row, column)) {
            return false;
        }

        if(shotHistory[row - 1][column - 1].state == '.') {
            return true;
        }
        cout << "You already fired at that. input another one." << endl;
    }
}

//this shows if its a hit or miss or if theres a boat near by on the grid
ShotResult resolveShot(const Grid& opponentGrid, Grid& shotHistory, int row, int column, int& opponentShipsRemaining) {
    ShotResult result = {
        opponentGrid[row][column].state == 'B',
        countAdjacentBoats(opponentGrid, row, column)
    };

    if(result.hit) {
        shotHistory[row][column].state = 'X';
        opponentShipsRemaining--;
    } else{
        shotHistory[row][column].state = 'O';
    }
    return result;
}

//shows if its a hit or miss
void displayShotResult(const string& playerName, int row, int column, const ShotResult& result, int shipsRemaining) {
    cout << playerName << " fired at row " << row + 1 << ", column " << column + 1 << ": " << (result.hit ? "Hit!" : "Miss!") << " " << shipsRemaining << " enemy ships remain. " << result.adjacentBoats << (result.adjacentBoats == 1 ? " boat is" : " boats are") << " touching that square, including diagonals." << endl;
}

#endif
