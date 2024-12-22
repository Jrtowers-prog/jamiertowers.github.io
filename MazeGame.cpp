#include <iostream>
#include <string>
#include <windows.h>
#include <chrono>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>
#include <cstdlib>
using namespace std;

vector<vector<char>> maze; //declaring global 2D vector to store map

class Maze {

    public:
        int enemyX, enemyY;
        int playerX, playerY;
        int rows = 15; //dimensions
        int cols = 15;
        
        void initialisemaze() {
            maze.resize(rows, vector<char>(cols, '#')); //initializes maze with dimensions cols and rows, also fills with #'s so that the carving algorithm works
            playerX = 1;
            playerY = 1;
            maze[playerX][playerY] = 'P'; //player's initial position indicated by P icon
        }

        void displaymaze() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << maze[i][j];
                }
                cout << endl;
            }
        };
        
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
            char playerdirection;
            cin >> playerdirection;
            while (!(playerdirection == 'W' || playerdirection == 'S' || playerdirection == 'A' || playerdirection == 'D' || playerdirection == 'w' || playerdirection == 's' || playerdirection == 'a' || playerdirection == 'd')) {
                cout << "Please enter a valid move.";
                cin >> playerdirection;
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

        void carve() {
            int startX = 1; //carve start
            int startY = 1;
            vector<vector<bool>> visited(rows, vector<bool>(cols, false)); //matrix for visited cells
            vector<pair<int, int>> directions = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}}; //directions stored in this vector, done in 2's to make sure we skip over walls
            vector<pair<int, int>> walls; //surrounding walls from current position to be carved
            bool isValid (int x, int y, vector<vector<bool>>& visited, int rows, int cols){  
              if (x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y]){
                return true;
              }
              else {
                return false;
              }
            }
            maze[startX][startY] = ' ';
            visited[startX][startY]= true;

            for (int i = o; i < directions.size(); i++){
                int wallX = startX + directions[i].first;
                int wallY = startY + directions[i].second;
                if (wallX < rows && wallX > 0 && wallY > 0 && wallY < cols){
                    walls.push_back({wallX,wallY});
                }
            }

            while (!(walls.length() == 0)){
                int carvechoice = rand() % walls.size();
                
            }

            

        }
};

class Enemy {
    public:
        char enemystart();
       
};

class Puzzle {
    public:
        char placekey();
        char placedoor();
        bool haskey();

};

int main() {
    Maze gameMaze;
    gameMaze.initialisemaze();
    gameMaze.carve();
    gameMaze.displaymaze();

    return 0;  
}
