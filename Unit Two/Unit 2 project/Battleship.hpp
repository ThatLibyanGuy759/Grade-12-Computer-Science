#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include <iostream>
#include <limits>
#include <string>
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
void displayGrid(const Grid& grid) {
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
void displayGrid(const vector<vector<int>>& grid) {
    for(const vector<int>& row : grid) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

//displays the values
void displayValues(const vector<int>& values) {
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
    //stops when theres 8 boats near by
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
        displayGrid(grid);

        if(!readCoordinate(grid, "Place ship " + to_string(i) + ": ", row, column)) {
            return;
        }

        //if there already is a boat there, as they cant stack boats
        if(grid[row - 1][column - 1].state != '.') {
            cout << "There is already a ship there." << endl;
        } else{
            grid[row - 1][column - 1].state = 'B';  // b for boat(ik shocking)
            i++;
        }
    }
}

//makes the symbol a dot so that it looks good(i chose a random symbol)
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
//this checks if you hit a bot or not
bool readPlayerShot(const string& playerName, const Grid& shotHistory, int& row, int& column) {
    cout << playerName << "'s shots:" << endl;
    displayGrid(shotHistory);

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
