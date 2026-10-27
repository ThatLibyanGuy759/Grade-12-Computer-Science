#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<char>> Grid;

void printGrid(const Grid& grid) {
    cout << "   ";
    for (int column = 1; column <= static_cast<int>(grid[0].size()); column++) {
        cout << column << " ";
    }
    cout << endl;

    for (int row = 0; row < static_cast<int>(grid.size()); row++) {
        cout << row + 1 << "  ";
        for (char cell : grid[row]) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

bool readCoordinate(const Grid& grid, const string& prompt, int& row, int& column) {
    while (true) {
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

        if (row >= 1 && row <= static_cast<int>(grid.size()) &&
            column >= 1 && column <= static_cast<int>(grid[0].size())) {
            return true;
        }

        cout << "That location is outside the grid. Try again." << endl;
    }
}

void placeBoats(Grid& grid, int boatCount, const string& playerName,
                bool placeRandomly, mt19937& randomGenerator) {
    if (placeRandomly) {
        uniform_int_distribution<int> randomRow(0, static_cast<int>(grid.size()) - 1);
        uniform_int_distribution<int> randomColumn(0, static_cast<int>(grid[0].size()) - 1);
        int boatsPlaced = 0;

        while (boatsPlaced < boatCount) {
            int row = randomRow(randomGenerator);
            int column = randomColumn(randomGenerator);
            if (grid[row][column] == '.') {
                grid[row][column] = 'B';
                boatsPlaced++;
            }
        }
        return;
    }

    cout << playerName << ", place your " << boatCount
         << " one-cell ships by entering a row and column." << endl;
    for (int boat = 1; boat <= boatCount;) {
        int row;
        int column;
        cout << "Your fleet:" << endl;
        printGrid(grid);

        if (!readCoordinate(grid, "Place ship " + to_string(boat) + ": ", row, column)) {
            return;
        }

        if (grid[row - 1][column - 1] != '.') {
            cout << "There is already a ship there. Try again." << endl;
        } else {
            grid[row - 1][column - 1] = 'B';
            boat++;
        }
    }
}

bool takePlayerShot(const string& playerName, const Grid& opponentFleet,
                    Grid& shotHistory, int& opponentShipsRemaining) {
    cout << playerName << "'s turn. Your shots (X = hit, O = miss, . = not tried):" << endl;
    printGrid(shotHistory);

    while (true) {
        int row;
        int column;
        if (!readCoordinate(shotHistory, "Choose a row and column to fire at: ", row, column)) {
            return false;
        }

        if (shotHistory[row - 1][column - 1] != '.') {
            cout << "You already fired at that location. Try again." << endl;
            continue;
        }

        if (opponentFleet[row - 1][column - 1] == 'B') {
            shotHistory[row - 1][column - 1] = 'X';
            opponentShipsRemaining--;
            cout << "Hit! " << opponentShipsRemaining << " enemy ships remain." << endl;
        } else {
            shotHistory[row - 1][column - 1] = 'O';
            cout << "Miss!" << endl;
        }

        return true;
    }
}

bool takeCpuShot(Grid& playerFleet, vector<vector<bool>>& cpuShotHistory,
                 int& playerShipsRemaining, mt19937& randomGenerator) {
    vector<pair<int, int>> availableShots;
    for (int row = 0; row < static_cast<int>(playerFleet.size()); row++) {
        for (int column = 0; column < static_cast<int>(playerFleet[0].size()); column++) {
            if (!cpuShotHistory[row][column]) {
                availableShots.push_back(make_pair(row, column));
            }
        }
    }

    if (availableShots.empty()) {
        return false;
    }

    uniform_int_distribution<int> chooseShot(0, static_cast<int>(availableShots.size()) - 1);
    pair<int, int> shot = availableShots[chooseShot(randomGenerator)];
    cpuShotHistory[shot.first][shot.second] = true;

    cout << "The CPU fired at row " << shot.first + 1
         << ", column " << shot.second + 1 << ". ";
    if (playerFleet[shot.first][shot.second] == 'B') {
        playerFleet[shot.first][shot.second] = 'X';
        playerShipsRemaining--;
        cout << "Hit! You have " << playerShipsRemaining << " ships left." << endl;
    } else {
        playerFleet[shot.first][shot.second] = 'O';
        cout << "Miss!" << endl;
    }

    cout << "Your fleet:" << endl;
    printGrid(playerFleet);
    return true;
}

int main() {
    const int boatCount = 10;
    bool singlePlayer = false;
    string input;
    string playerOneName;
    string playerTwoName;
    int width;
    int height;
    mt19937 randomGenerator(random_device{}());

    while (true) {
        cout << "Play against a friend? (yes/no): ";
        if (!(cin >> input)) {
            return 0;
        }
        if (input == "yes" || input == "Yes" || input == "no" || input == "No") {
            singlePlayer = (input == "no" || input == "No");
            break;
        }
        cout << "Please enter yes or no." << endl;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Player 1 name: ";
    if (!getline(cin, playerOneName)) {
        return 0;
    }
    if (playerOneName.empty()) {
        playerOneName = "Player 1";
    }

    if (singlePlayer) {
        playerTwoName = "CPU";
    } else {
        cout << "Player 2 name: ";
        if (!getline(cin, playerTwoName)) {
            return 0;
        }
        if (playerTwoName.empty()) {
            playerTwoName = "Player 2";
        }
    }

    cout << "What width do you want your grid? ";
    if (!(cin >> width)) {
        cout << "Please enter a number for the grid width." << endl;
        return 1;
    }
    cout << "What height do you want your grid? ";
    if (!(cin >> height)) {
        cout << "Please enter a number for the grid height." << endl;
        return 1;
    }

    if (width <= 0 || height <= 0 ||
        static_cast<long long>(width) * height < boatCount) {
        cout << "The grid must have positive dimensions and at least " << boatCount
             << " spaces for the ships." << endl;
        return 1;
    }

    Grid playerOneFleet(height, vector<char>(width, '.'));
    Grid playerTwoFleet(height, vector<char>(width, '.'));
    Grid playerOneShots(height, vector<char>(width, '.'));
    Grid playerTwoShots(height, vector<char>(width, '.'));
    vector<vector<bool>> cpuShotHistory(height, vector<bool>(width, false));

    placeBoats(playerOneFleet, boatCount, playerOneName, false, randomGenerator);
    if (cin.eof()) {
        return 0;
    }
    if (singlePlayer) {
        placeBoats(playerTwoFleet, boatCount, playerTwoName, true, randomGenerator);
        cout << "The CPU has hidden its ships." << endl;
    } else {
        cout << "Pass the device to " << playerTwoName
             << ". Player 1, please look away while they place ships." << endl;
        placeBoats(playerTwoFleet, boatCount, playerTwoName, false, randomGenerator);
        if (cin.eof()) {
            return 0;
        }
        cout << "Ships are placed. Players, take turns and don't peek at each other's fleet." << endl;
    }

    int playerOneShipsRemaining = boatCount;
    int playerTwoShipsRemaining = boatCount;
    bool playerOneTurn = true;

    while (playerOneShipsRemaining > 0 && playerTwoShipsRemaining > 0) {
        if (playerOneTurn) {
            if (!takePlayerShot(playerOneName, playerTwoFleet, playerOneShots,
                                playerTwoShipsRemaining)) {
                return 0;
            }
        } else if (singlePlayer) {
            if (!takeCpuShot(playerOneFleet, cpuShotHistory, playerOneShipsRemaining,
                             randomGenerator)) {
                cout << "The CPU has no shots left." << endl;
                break;
            }
        } else {
            if (!takePlayerShot(playerTwoName, playerOneFleet, playerTwoShots,
                                playerOneShipsRemaining)) {
                return 0;
            }
        }

        if (playerOneShipsRemaining == 0 || playerTwoShipsRemaining == 0) {
            break;
        }

        if (!singlePlayer) {
            cout << "Pass the device to "
                 << (playerOneTurn ? playerTwoName : playerOneName)
                 << " for their turn." << endl;
        }
        playerOneTurn = !playerOneTurn;
    }

    if (playerOneShipsRemaining == 0) {
        cout << playerTwoName << " wins!" << endl;
    } else if (playerTwoShipsRemaining == 0) {
        cout << playerOneName << " wins!" << endl;
    }
}
