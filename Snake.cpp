#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Game variables
bool gameOver;
const int width = 30;
const int height = 25;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;

// Directions
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Game setup
void Setup() {
    gameOver = false;
    dir = RIGHT;  // Default direction (Fixes no movement bug)
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
    nTail = 0;
}

// Draw the game
void Draw() {
    SetCursorPosition(0, 0);  // Clear screen without flicker

    // Top border
    for (int i = 0; i < width + 3; i++) cout << "=";
    cout << endl;

    // Map drawing
    for (int i = 0; i < height; i++) {
        cout << "||";  // Left border

        for (int j = 0; j < width; j++) {
            if (i == y && j == x)
                cout << "~";  // Snake head
            else if (i == foodY && j == foodX)
                cout << "*";  // Food
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";  // Snake tail
                        print = true;
                        break;
                    }
                }
                if (!print) cout << " ";
            }
        }

        cout << "||" << endl;  // Right border
    }

    // Bottom border
    for (int i = 0; i < width + 3; i++) cout << "=";
    cout << endl;

    // Score and controls
    cout << "Score: " << score << endl;
    cout << "Controls: W = up | S = down | A = left | D = right | X = exit\n";
}

// Take input
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
            case 'A':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
            case 'D':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
            case 'W':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
            case 'S':
                if (dir != UP) dir = DOWN;
                break;
            case 'x':
            case 'X':
                gameOver = true;
                break;
        }
    }
}

// Game logic
void Logic() {
    // Move tail
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move head
    switch (dir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
    }

    // Collision with wall
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    // Collision with tail
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // Eat food
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++;
    }
}

// Main
int main() {
    Setup();

    // Hide cursor for clean output
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    // Game loop
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);  // Control speed
    }

    // Game over screen
    cout << "\nGame Over!" << endl;
    cout << "Final Score: " << score << endl;
    system("pause");
    return 0;
}
