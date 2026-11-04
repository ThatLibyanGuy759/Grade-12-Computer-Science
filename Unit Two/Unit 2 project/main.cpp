#include "Battleship.hpp"

using namespace std;

int main() {
    string input;
    string playerOneName;
    string playerTwoName;
    int boatCount;
    int width;
    int height;
    bool singlePlayer;
    mt19937 randomGenerator(random_device{}());

    cout << "Play against the CPU? (yes/no): ";
    if (!(cin >> input)) {
        return 0;
    }
    if (input == "yes" || input == "Yes") {
        singlePlayer = true;
        playerTwoName = "CPU";
    } else if (input == "no" || input == "No") {
        singlePlayer = false;
    } else {
        cout << "Please enter yes or no." << endl;
        return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Player 1 name: ";
    if (!getline(cin, playerOneName)) {
        return 0;
    }
    if (playerOneName.empty()) {
        playerOneName = "Player 1";
    }

    if (!singlePlayer) {
        cout << "Player 2 name: ";
        if (!getline(cin, playerTwoName)) {
            return 0;
        }
        if (playerTwoName.empty()) {
            playerTwoName = "Player 2";
        }
    }

    cout << "How many ships should each player place? ";
    if (!(cin >> boatCount) || boatCount <= 0) {
        cout << "Please enter a positive number of ships." << endl;
        return 1;
    }

    cout << "What width do you want your grid? ";
    if (!(cin >> width)) {
        cout << "Please enter a number for the grid width." << endl;
        return 1;
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

    while (true) {
        Grid playerOneGrid = createGrid(height, width);
        Grid playerTwoGrid = createGrid(height, width);
        Grid playerOneShots = createGrid(height, width);
        Grid playerTwoShots = createGrid(height, width);

        cout << playerOneName << ", place your ships while " << playerTwoName
             << " looks away." << endl;
        placeBoats(playerOneGrid, boatCount, playerOneName);
        if (cin.eof()) {
            return 0;
        }

        if (singlePlayer) {
            placeCpuBoats(playerTwoGrid, boatCount, randomGenerator);
            cout << "The CPU has hidden its ships." << endl;
        } else {
            cout << "Pass the device to " << playerTwoName << ". "
                 << playerOneName << ", please look away." << endl;
            placeBoats(playerTwoGrid, boatCount, playerTwoName);
            if (cin.eof()) {
                return 0;
            }
        }

        int playerOneShipsRemaining = boatCount;
        int playerTwoShipsRemaining = boatCount;
        bool playerOneWins = false;
        bool playerTwoWins = false;
        bool boardExhausted = false;
        int round = 1;

        while (playerOneShipsRemaining > 0 && playerTwoShipsRemaining > 0) {
            if (!hasUnfiredSquares(playerOneShots) ||
                !hasUnfiredSquares(playerTwoShots)) {
                boardExhausted = true;
                break;
            }

            int playerOneRow;
            int playerOneColumn;
            cout << "Round " << round << ": Pass the device to " << playerOneName
                 << ". " << playerTwoName << ", please look away." << endl;
            if (!readPlayerShot(playerOneName, playerOneShots,
                                playerOneRow, playerOneColumn)) {
                return 0;
            }

            int playerTwoRow;
            int playerTwoColumn;
            if (singlePlayer) {
                if (!chooseCpuShot(playerTwoShots, randomGenerator,
                                   playerTwoRow, playerTwoColumn)) {
                    boardExhausted = true;
                    break;
                }
            } else {
                cout << "Pass the device to " << playerTwoName << ". "
                     << playerOneName << ", please look away." << endl;
                if (!readPlayerShot(playerTwoName, playerTwoShots,
                                    playerTwoRow, playerTwoColumn)) {
                    return 0;
                }
            }

            ShotResult playerOneResult =
                resolveShot(playerTwoGrid, playerOneShots,
                            playerOneRow - 1, playerOneColumn - 1,
                            playerTwoShipsRemaining);
            ShotResult playerTwoResult =
                resolveShot(playerOneGrid, playerTwoShots,
                            playerTwoRow - 1, playerTwoColumn - 1,
                            playerOneShipsRemaining);

            cout << "Both shots are revealed:" << endl;
            displayShotResult(playerOneName, playerOneRow - 1,
                              playerOneColumn - 1, playerOneResult,
                              playerTwoShipsRemaining);
            displayShotResult(playerTwoName, playerTwoRow - 1,
                              playerTwoColumn - 1, playerTwoResult,
                              playerOneShipsRemaining);

            playerOneWins = playerTwoShipsRemaining == 0;
            playerTwoWins = playerOneShipsRemaining == 0;
            round++;
        }

        if (boardExhausted) {
            cout << "No unshot squares remain. Both players lose." << endl;
        } else if (playerOneWins && playerTwoWins) {
            cout << "Both players sank the last ship in the same round. "
                 << "It's a draw; both lose!" << endl;
        } else if (playerOneWins) {
            cout << playerOneName << " wins!" << endl;
        } else if (playerTwoWins) {
            cout << playerTwoName << " wins!" << endl;
        }

        cout << "Would you like to play another game with new boat placements? (yes/no): ";
        while (true) {
            if (!(cin >> input)) {
                return 0;
            }
            if (input == "no" || input == "No") {
                return 0;
            }
            if (input == "yes" || input == "Yes") {
                break;
            }
            cout << "Please enter yes or no: ";
        }
    }
}
