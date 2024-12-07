#include <iostream>
#include <vector>
using namespace std;

class TicTacToe {
    vector<vector<char>> board;
    char currentPlayer;

public:
    TicTacToe() : board(3, vector<char>(3, ' ')), currentPlayer('X') {}

    void initializeGame() {
        for (auto& row : board)
            fill(row.begin(), row.end(), ' ');
        currentPlayer = 'X';
    }

    void displayBoard() {
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << " " << board[i][j] << " ";
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "---+---+---\n";
        }
    }

    bool makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            cout << "Invalid move. Try again.\n";
            return false;
        }
        board[row][col] = currentPlayer;
        return true;
    }

    bool checkWin() {
        for (int i = 0; i < 3; ++i) {
            // Check rows and columns
            if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
                (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer))
                return true;
        }
        // Check diagonals
        if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
            (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer))
            return true;

        return false;
    }

    bool checkDraw() {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }
};

void playGame() {
    TicTacToe game;
    game.initializeGame();

    cout << "Welcome to Tic Tac Toe!\nPlayer X goes first.\n";
    game.displayBoard();

    while (true) {
        int row, col;
        cout << "Player " << game.getCurrentPlayer() << "'s turn.\n";
        cout << "Enter your move (row and column, 1-3): ";
        cin >> row >> col;

        if (!cin || row < 1 || row > 3 || col < 1 || col > 3) {
            cout << "Invalid input. Please enter numbers between 1 and 3.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (game.makeMove(row - 1, col - 1)) {
            game.displayBoard();
            if (game.checkWin()) {
                cout << "Player " << game.getCurrentPlayer() << " wins!\n";
                break;
            }
            if (game.checkDraw()) {
                cout << "It's a draw!\n";
                break;
            }
            game.switchPlayer();
        }
    }

    char choice;
    cout << "Would you like to play again? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        playGame();
    } else {
        cout << "Thanks for playing!\n";
    }
}

int main() {
    playGame();
    return 0;
}
