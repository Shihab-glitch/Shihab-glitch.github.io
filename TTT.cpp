#include <iostream>
#include <vector>
#include <string>

// Global constants for board size and player marks
const int BOARD_SIZE = 3;
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY_SPOT = ' ';

// Function to initialize the game board
void initializeBoard(std::vector<std::vector<char>>& board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = EMPTY_SPOT;
        }
    }
}

// Function to display the current state of the board
void displayBoard(const std::vector<std::vector<char>>& board) {
    system("cls"); // For Windows, use "clear" for Linux/macOS
    std::cout << "\n Tic-Tac-Toe\n\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << " " << board[i][j];
            if (j < BOARD_SIZE - 1) {
                std::cout << " |";
            }
        }
        std::cout << std::endl;
        if (i < BOARD_SIZE - 1) {
            std::cout << "--- --- ---\n";
        }
    }
    std::cout << std::endl;
}

// Function to get player's move
bool getPlayerMove(std::vector<std::vector<char>>& board, char currentPlayer, int& row, int& col) {
    while (true) {
        std::cout << "Player " << currentPlayer << ", enter your move (row and column, e.g., 1 2): ";
        std::cin >> row >> col;

        // Adjust for 0-based indexing
        row--;
        col--;

        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY_SPOT) {
            return true; // Valid move
        } else {
            std::cout << "Invalid move. Please try again.\n";
            // Clear input buffer in case of invalid non-integer input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Function to check for a win
bool checkWin(const std::vector<std::vector<char>>& board, char player) {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    // Check columns
    for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Function to check for a draw
bool checkDraw(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == EMPTY_SPOT) {
                return false; // Still empty spots, so not a draw yet
            }
        }
    }
    return true; // All spots filled, no winner, so it's a draw
}

int main() {
    std::vector<std::vector<char>> board(BOARD_SIZE, std::vector<char>(BOARD_SIZE));
    char currentPlayer = PLAYER_X;
    bool gameWon = false;
    bool gameDraw = false;
    int row, col;

    initializeBoard(board);

    while (!gameWon && !gameDraw) {
        displayBoard(board);
        if (getPlayerMove(board, currentPlayer, row, col)) {
            board[row][col] = currentPlayer; // Update board with valid move

            gameWon = checkWin(board, currentPlayer);
            if (gameWon) {
                displayBoard(board);
                std::cout << "Player " << currentPlayer << " wins!\n";
            } else {
                gameDraw = checkDraw(board);
                if (gameDraw) {
                    displayBoard(board);
                    std::cout << "It's a draw!\n";
                } else {
                    // Switch players
                    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                }
            }
        }
    }

    std::cout << "Game Over!\n";
    return 0;
}