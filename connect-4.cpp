
// connect-4.cpp : A complete implementation of connect 4 in c++.
// Visual Code IDE

#include <iostream>
#include <map>
using namespace std;

// Stores each player's info
struct playerInfo
{
    string playerName;
    char playerID;
    int score;
};

// Stores the position a player played in
struct position
{
    int x;
    int y;
};

//sets the rows and columns for the gameboard
const int ROWS = 6;
const int COLS = 7;
char game_board[ROWS][COLS] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '}
};

map<int, int> rowsMap; // Keeps the pieces from going out of bounds when dropped into board
position currentMove; // Stores the position a player played in

// Declared functions
void printBoard();
void reset();
void dropPiece(playerInfo);
bool playerWon(playerInfo&);
bool checkDirection(string, playerInfo, int&);
bool isValidPosition(int, int);

int main()
{
    int movesPlayed = 0; // Keeps track of the total number of moves played
    int restart;

    // Creates two players for the game
    playerInfo playerOne, playerTwo;

    // Player 1's info
    cout << "Player 1 enter your name: ";
    cin >> playerOne.playerName;
    playerOne.playerID = 'X';
    playerOne.score = 0;

    // Player 2's info
    cout << "Player 2 enter your name: ";
    cin >> playerTwo.playerName;
    playerTwo.playerID = 'O';
    playerTwo.score = 0;

    // Prints the starting scores
    cout << endl;
    cout << "Scores: " << endl;
    cout << playerOne.playerName << ": " << playerOne.score << endl;
    cout << playerTwo.playerName << ": " << playerTwo.score << endl;

    reset();

    while (true) {
        // Player 1's turn
        dropPiece(playerOne);
        movesPlayed++;

        // Checks if player 1 won
        if (playerWon(playerOne)) {
            // Prints out the scores
            cout << endl;
            cout << "Scores: " << endl;
            cout << playerOne.playerName << " (" << playerOne.playerID << ") score: " << playerOne.score << endl;
            cout << playerTwo.playerName << " (" << playerTwo.playerID << ") score: " << playerTwo.score << endl;

            // Asks if the user wants to play again
            cout << endl;
            cout << "Enter '0' to play again, enter anything else to stop: ";
            cin >> restart;

            // Resets game
            if (restart == 0) {
                reset();
                movesPlayed = 0;
            }

            else
                break;
        }

        // Player 2's turn
        dropPiece(playerTwo);
        movesPlayed++;

        // Checks if player 2 won
        if (playerWon(playerTwo)) {
            // Prints out the scores
            cout << endl;
            cout << "Scores: " << endl;
            cout << playerOne.playerName << " (" << playerOne.playerID << ") score: " << playerOne.score << endl;
            cout << playerTwo.playerName << " (" << playerTwo.playerID << ") score: " << playerTwo.score << endl;

            // Asks if the user wants to play again
            cout << endl;
            cout << "Enter '0' to play again, enter anything else to stop: ";
            cin >> restart;

            // Resets game
            if (restart == 0) {
                reset();
                movesPlayed = 0;
            }

            else
                break;
        }

        // Checks board for a tie
        if (movesPlayed == ROWS * COLS) {
            cout << "It's a tie" << endl;

            cout << endl;
            cout << "Scores: " << endl;
            cout << playerOne.playerName << " (" << playerOne.playerID << ") score: " << playerOne.score << endl;
            cout << playerTwo.playerName << " (" << playerTwo.playerID << ") score: " << playerTwo.score << endl;

            // Asks if the user wants to play again
            cout << endl;
            cout << "Enter '0' to play again, enter anything else to stop: ";
            cin >> restart;

            // Resets game
            if (restart == 0) {
                reset();
                movesPlayed = 0;
            }

            else
                break;
        }
    }
    return 0;
}

// Prints the game board
void printBoard() {
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "  +---+---+---+---+---+---+---+" << endl;
        cout << "  | " <<
            game_board[i][0] << " | " <<
            game_board[i][1] << " | " <<
            game_board[i][2] << " | " <<
            game_board[i][3] << " | " <<
            game_board[i][4] << " | " <<
            game_board[i][5] << " | " <<
            game_board[i][6] << " | " << endl;
    }
    cout << "  +---+---+---+---+---+---+---+" << endl;
    cout << "    1   2   3   4   5   6   7  " << endl;
    cout << endl;
}

// Resets the game board
void reset() {
    for (int i = 0; i < ROWS; i++)
        memset(game_board, ' ', ROWS * COLS);

    for (int i = 1; i <= COLS; i++)
        rowsMap[i] = ROWS - 1;

    printBoard();
}

// Drops piece to the board
void dropPiece(playerInfo player) {
    // Prompts the player to select a spot
    int column;
    cout << player.playerName + " (" + player.playerID + ")" + " select a column: ";
    cin >> column;

    // Checks if the selected spot is within bounds
    while (column < 1 || column > COLS) {
        cout << "\nOut of Bounds.\n";
        cout << player.playerName + " (" + player.playerID + ")" + " select a column: ";
        cin >> column;
    }

    // Checks if the selected row is filled to the top
    int row = rowsMap[column];
    while (row < 0) {
        cout << "\nThis column is full.\n";
        cout << player.playerName + " (" + player.playerID + ")" + " select a column: ";
        cin >> column;

        while (column < 1 || column > COLS) {
            cout << "\nOut of Bounds.\n";
            cout << player.playerName + " (" + player.playerID + ")" + " select a column: ";
            cin >> column;
        }

        row = rowsMap[column];
    }

    // Places the piece on the board and stores the position the player played in
    game_board[row][column - 1] = player.playerID;
    rowsMap[column] -= 1;
    currentMove.x = row;
    currentMove.y = column - 1;

    printBoard();
}

// Checks the board for a win state
bool playerWon(playerInfo &player) {
    bool checkDown, checkLeft, checkRight, checkTopRight, checkTopLeft, checkBottomRight, checkBottomLeft;
    int count; // Checks adjacent and diagonal pieces

    string winStatement = player.playerName + " won!";

    count = 0;
    // Checks downward for a win
    checkDown = checkDirection("down", player, count);
    if (checkDown) {
        cout << winStatement << endl;
        player.score += 1;
        return true;
    }

    count = 0;
    // Checks left and right for a win
    checkLeft = checkDirection("left", player, count);
    checkRight = checkDirection("right", player, count);
    if (checkLeft || checkRight) {
        cout << winStatement << endl;
        player.score += 1;
        return true;
    }

    /* CHECKS DIAGONALS FOR A WIN*/

    count = 0;
    // Checks top right and bottom left for a win
    checkTopRight = checkDirection("topRight", player, count);
    checkBottomLeft = checkDirection("bottomLeft", player, count);
    if (checkTopRight || checkBottomLeft) {
        cout << winStatement << endl;
        player.score += 1;
        return true;
    }

    count = 0;
    // Checks top left and bottom right for a win
    checkTopLeft = checkDirection("topLeft", player, count);
    checkBottomRight = checkDirection("bottomRight", player, count);
    if (checkBottomRight || checkTopLeft) {
        cout << winStatement << endl;
        player.score += 1;
        return true;
    }
    return false;
}

// Checks every direction on the game board for a win
// Checks downwards, left, right, and diagonals
bool checkDirection(string direction, playerInfo player, int &count) {
    for (int i = 1; i <= 3; i++) {
        // Gets the x and y values of the position the current player played in
        int x = currentMove.x;
        int y = currentMove.y;

        // Down
        if (direction.compare("down") == 0)
            x += i;

        // Left
        else if (direction.compare("left") == 0)
            y -= i;

        // Right
        else if (direction.compare("right") == 0)
            y += i;

        // Top right
        else if (direction.compare("topRight") == 0) {
            x -= i;
            y += i;
        }

        // Top left
        else if (direction.compare("topLeft") == 0) {
            x -= i;
            y -= i;
        }

        // Bottom right
        else if (direction.compare("bottomRight") == 0) {
            x += i;
            y += i;
        }

        // Bottom left
        else if (direction.compare("bottomLeft") == 0) {
            x += i;
            y -= i;
        }

        if (isValidPosition(x, y)) {
            if (game_board[x][y] == player.playerID)
                count++;

            else
                break;

            // Three pieces have been found next to the current piece
            if (count == 3)
                return true;
        }
    }
    return false;
}

// Checks if a position on the board is valid - Not out of bounds
bool isValidPosition(int x, int y) {
    if (x >= 0 && x < ROWS && y >= 0 && y < COLS)
        return true;
    return false;
}
