#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
using namespace std;

class Maze {
public:
    int enemyX, enemyY;
    int playerX, playerY;
    int rows, cols;

    // Store both the maze and visitedcells in the class
    vector<vector<char>> maze;
    vector<vector<bool>> visitedcells;

    // Constructor
    Maze() {
        rows = 25;
        cols = 25;
        // Make the maze 25x25 of '#' initially
        maze.resize(rows, vector<char>(cols, '#'));
        // Make visitedcells the same size, all false
        visitedcells.resize(rows, vector<bool>(cols, false));

        enemyX = enemyY = 0;
        playerX = playerY = 0;
    }

    bool isValid(int x, int y, vector<vector<bool>>& visited) {
        return x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y];
    }

    // Replaces "initialisemaze()" since the constructor does it
    // But you can keep it if you prefer manually resetting the maze each time.
    void initialisemaze() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                maze[i][j] = '#';
                visitedcells[i][j] = false;
            }
        }
    }

    void displaymaze() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << maze[i][j];
            }
            cout << endl;
        }
    }

    // Simple DFS
    void carveDFS(int x, int y) {
        visitedcells[x][y] = true;
        maze[x][y] = ' ';

        // directions is a 4x2 array
        int directions[4][2] = {
            {-2, 0},  // up
            {2, 0},   // down
            {0, -2},  // left
            {0, 2}    // right
        };

        // shuffle directions for randomness
        for (int i = 0; i < 4; i++) {
            int r = rand() % 4;
            // swap directions[i] with directions[r]
            int tmpX = directions[i][0];
            int tmpY = directions[i][1];
            directions[i][0] = directions[r][0];
            directions[i][1] = directions[r][1];
            directions[r][0] = tmpX;
            directions[r][1] = tmpY;
        }

        // check each direction
        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];

            // bounds check
            if (nx > 0 && nx < rows - 1 && ny > 0 && ny < cols - 1) {
                if (!visitedcells[nx][ny]) {
                    // carve the wall between (x,y) and (nx,ny)
                    int midX = (x + nx) / 2;
                    int midY = (y + ny) / 2;
                    maze[midX][midY] = ' ';

                    // recurse
                    carveDFS(nx, ny);
                }
            }
        }
    }

    // Carve wrapper
    void carve() {
        // Reset everything to walls + unvisited
        initialisemaze();
        // Start the DFS at (1,1)
        carveDFS(1, 1);
    }

    // The rest of your methods
    void placeCharacters() {
        playerX = 1;
        playerY = 1;
        maze[playerX][playerY] = 'P';

        enemyX = rows - 2;
        enemyY = cols - 2;
        maze[enemyX][enemyY] = 'E';
    }

    void moveEnemy() {
        int enemydirection = (rand() % 4) + 1;
        switch (enemydirection) {
        case 1:
            if ((maze[enemyX - 1][enemyY] != '#') && ((enemyX - 1) >= 0)) {
                maze[enemyX][enemyY] = ' ';
                enemyX--;
                maze[enemyX][enemyY] = 'E';
            }
            break;
        case 2:
            if ((maze[enemyX + 1][enemyY] != '#') && ((enemyX + 1) < rows)) {
                maze[enemyX][enemyY] = ' ';
                enemyX++;
                maze[enemyX][enemyY] = 'E';
            }
            break;
        case 3:
            if ((maze[enemyX][enemyY - 1] != '#') && ((enemyY - 1) >= 0)) {
                maze[enemyX][enemyY] = ' ';
                enemyY--;
                maze[enemyX][enemyY] = 'E';
            }
            break;
        case 4:
            if ((maze[enemyX][enemyY + 1] != '#') && ((enemyY + 1) < cols)) {
                maze[enemyX][enemyY] = ' ';
                enemyY++;
                maze[enemyX][enemyY] = 'E';
            }
            break;
        }
    }

    void movePlayer() {
        char playerdirection = _getch();
        while (!(playerdirection == 'W' || playerdirection == 'S' || playerdirection == 'A' || playerdirection == 'D' || playerdirection == 'w' || playerdirection == 's' || playerdirection == 'a' || playerdirection == 'd')) {
            cout << "Please enter a valid move.";
              playerdirection = _getch();
        }
        maze[playerX][playerY] = ' ';
        if ((playerdirection == 'W' || playerdirection == 'w') && (maze[playerX - 1][playerY] != '#') && ((playerX - 1) >= 0)) {
            playerX--;
            maze[playerX][playerY] = 'P';
        }
        if ((playerdirection == 'S' || playerdirection == 's') && (maze[playerX + 1][playerY] != '#') && ((playerX + 1) < rows)) {
            playerX++;
            maze[playerX][playerY] = 'P';
        }
        if ((playerdirection == 'A' || playerdirection == 'a') && (maze[playerX][playerY - 1] != '#') && ((playerY - 1) >= 0)) {
            playerY--;
            maze[playerX][playerY] = 'P';
        }
        if ((playerdirection == 'D' || playerdirection == 'd') && (maze[playerX][playerY + 1] != '#') && ((playerY + 1) < cols)) {
            playerY++;
            maze[playerX][playerY] = 'P';
        }

    }
};


int main() {
    srand(time(0));
    Maze gameMaze;

    // If you do carve() inside the constructor, you can skip this,
    // but let's keep it explicit:
    gameMaze.carve();
    gameMaze.placeCharacters();

    system("cls");

    while (true) {
        // Clear screen by resetting cursor
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD Position = { 0, 0 };
        SetConsoleCursorPosition(hOut, Position);

        gameMaze.displaymaze();

        if (_kbhit()) {
            gameMaze.movePlayer();
        }

        gameMaze.moveEnemy();
        Sleep(100);
    }
    return 0;
}
