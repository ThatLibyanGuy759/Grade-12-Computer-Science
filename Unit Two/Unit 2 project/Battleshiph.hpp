#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Cell {
    int row;
    int column;
    char state;
};

struct ShotResult {
    bool hit;
    int adjacentBoats;
};

typedef vector<vector<Cell>> Grid;

Grid createGrid(int height, int width) {
    Grid grid(height, vector<Cell>(width));
    for(int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            grid[row][column] = {row, column, '.'};
        }
    }
    return grid;
}

void displayGrid(const Grid& grid) {
    if(grid.empty() || grid[0].empty()) {
        return;
    }

    cout << "   ";
    for(int column = 1; column <= static_cast<int>(grid[0].size()); column++) {
        cout << column << " ";
    }
    cout << endl;

    for(int row = 0; row < static_cast<int>(grid.size()); row++) {
        cout << row + 1 << "  ";
        for (const Cell& cell : grid[row]) {
            cout << cell.state << " ";
        }
        cout << endl;
    }
}

void displayGrid(const vector<vector<int>>& grid) {
    for(const vector<int>& row : grid) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

void displayGrid(const vector<int>& values) {
    for(int value : values) {
        cout << value << " ";
    }
    cout << endl;
}

bool readCoordinate(const Grid& grid, const string& prompt, int& row, int& column) {
    while(true) {
        cout << prompt;
        if (!(cin >> row >> column)) {
            if (cin.eof()) {
                return false;
            }

            cout << "Enter two numbers. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if(row >= 1 && row <= static_cast<int>(grid.size()) &&
            column >= 1 && column <= static_cast<int>(grid[0].size())) {
            return true;
        }

        cout << "That location is outside the grid. Try again." << endl;
    }
}

int countAdjacentBoats(const Grid& grid, int row, int column, int direction = 0) {
    static const int rowOffsets[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int columnOffsets[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    if(direction == 8) {
        return 0;
    }

    int adjacentRow = row + rowOffsets[direction];
    int adjacentColumn = column + columnOffsets[direction];
    int boatAtPosition = 0;

    if (adjacentRow >= 0 && adjacentRow < static_cast<int>(grid.size()) &&
        adjacentColumn >= 0 &&
        adjacentColumn < static_cast<int>(grid[0].size()) &&
        grid[adjacentRow][adjacentColumn].state == 'B') {
        boatAtPosition = 1;
    }

    return boatAtPosition + countAdjacentBoats(grid, row, column, direction + 1);
}

void placeBoats(Grid& grid, int boatCount, const string& playerName) {
    cout << playerName << ", place your " << boatCount << " one-cell ships by entering a row and column." << endl;

    for(int boat = 1; boat <= boatCount;) {
        int row;
        int column;
        cout << "Your fleet:" << endl;
        displayGrid(grid);

        if(!readCoordinate(grid, "Place ship " + to_string(boat) + ": ", row, column)) {
            return;
        }

        if(grid[row - 1][column - 1].state != '.') {
            cout << "There is already a ship there. Try again." << endl;
        } else{
            grid[row - 1][column - 1].state = 'B';
            boat++;
        }
    }
}

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

bool readPlayerShot(const string& playerName, const Grid& shotHistory, int& row, int& column) {
    cout << playerName << "'s shots (X = hit, O = miss, . = not tried):" << endl;
    displayGrid(shotHistory);

    while(true) {
        if(!readCoordinate(shotHistory, "Choose a row and column to fire at: ", row, column)) {
            return false;
        }

        if (shotHistory[row - 1][column - 1].state == '.') {
            return true;
        }
        cout << "You already fired at that location. Try again." << endl;
    }
}

ShotResult resolveShot(const Grid& opponentFleet, Grid& shotHistory, int row, int column, int& opponentShipsRemaining) {
    ShotResult result = {
        opponentFleet[row][column].state == 'B',
        countAdjacentBoats(opponentFleet, row, column)
    };

    if(result.hit) {
        shotHistory[row][column].state = 'X';
        opponentShipsRemaining--;
    } else{
        shotHistory[row][column].state = 'O';
    }
    return result;
}

void displayShotResult(const string& playerName, int row, int column,
                       const ShotResult& result, int shipsRemaining) {
    cout << playerName << " fired at row " << row + 1 << ", column " << column + 1 << ": " << (result.hit ? "Hit!" : "Miss!") << " " << shipsRemaining << " enemy ships remain. " << result.adjacentBoats << (result.adjacentBoats == 1 ? " boat is" : " boats are") << " touching that square, including diagonals." << endl;
}

#endif
