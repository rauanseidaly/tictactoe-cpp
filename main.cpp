#include <iostream>
#include <vector>
using namespace std;

enum class Player { None, X, O };

class TicTacToe {
    vector<vector<Player>> board;
    Player currentPlayer;
    bool gameWon;

public:
    TicTacToe() : board(3, vector<Player>(3, Player::None)), currentPlayer(Player::X), gameWon(false) {}

    void displayBoard() const {
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                char symbol = getSymbol(board[i][j]);
                cout << " " << symbol << " ";
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "---+---+---\n";
        }
    }

    bool makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != Player::None || gameWon)
            return false;

        board[row][col] = currentPlayer;
        if (checkWin(row, col)) {
            gameWon = true;
        } else {
            currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
        }
        return true;
    }

    bool isGameOver() const {
        if (gameWon) {
            cout << "Player " << (currentPlayer == Player::X ? "X" : "O") << " wins!\n";
            return true;
        }
        if (isDraw()) {
            cout << "It's a draw!\n";
            return true;
        }
        return false;
    }

    void reset() {
        board = vector<vector<Player>>(3, vector<Player>(3, Player::None));
        currentPlayer = Player::X;
        gameWon = false;
    }

    Player getCurrentPlayer() const { return currentPlayer; }

private:
    char getSymbol(Player player) const {
        switch (player) {
            case Player::X: return 'X';
            case Player::O: return 'O';
            default: return ' ';
        }
    }

    bool checkWin(int row, int col) {
        Player p = board[row][col];
        // Check row, column, and diagonals
        return (board[row][0] == p && board[row][1] == p && board[row][2] == p) ||
               (board[0][col] == p && board[1][col] == p && board[2][col] == p) ||
               (row == col && board[0][0] == p && board[1][1] == p && board[2][2] == p) ||
               (row + col == 2 && board[0][2] == p && board[1][1] == p && board[2][0] == p);
    }

    bool isDraw() const {
        for (const auto& row : board) {
            for (const auto& cell : row) {
                if (cell == Player::None) return false;
            }
        }
        return !gameWon;
    }
};

int main() {
    TicTacToe game;
    int row, col;

    cout << "Welcome to Tic Tac Toe!\n";
    cout << "Player X goes first.\n";
    game.displayBoard();

    while (!game.isGameOver()) {
        cout << "Player " << (game.getCurrentPlayer() == Player::X ? "X" : "O") << "'s turn.\n";
        cout << "Enter your move (row and column, 1-3): ";
        cin >> row >> col;

        if (game.makeMove(row - 1, col - 1)) {
            game.displayBoard();
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    cout << "Game over! Thanks for playing.\n";
    return 0;
}
