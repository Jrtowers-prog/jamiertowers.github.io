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
        bool isValid (int x, int y, vector<vector<bool>>& visitedcells){  //checks if cell is valid for carving (not outside paramters of map), visitedcells vector is 2d and passed by reference meaning later functions can directly modify the values in this vector
              return (x >= 0 && x < rows && y >= 0 && y < cols && !visitedcells[x][y]);
        }
        
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
            vector<vector<bool>> visitedcells(rows, vector<bool>(cols, false));
            vector<pair<int, int>> directions = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}}; //directions stored in this vector, done in 2's to make sure we skip over walls
            vector<pair<int, int>> walls; //surrounding walls from current position to be carved
            maze[startX][startY] = ' ';
            visitedcells[startX][startY]= true;

            for (int i = 0; i < directions.size(); i++){  //adding surrounding walls to walls list
                int wallX = startX + directions[i].first;
                int wallY = startY + directions[i].second;
                if (wallX < rows && wallX > 0 && wallY > 0 && wallY < cols){  //checking if surrounding walls are valid before adding to list
                    walls.push_back({wallX,wallY});
                }
            }

            while (!(walls.size() == 0)){ //loop iterates until surrounding walls are all used
                int carvechoice = rand() % walls.size(); //pick number from 1 to number of surrounding walls
                pair<int,int> wallchoice = walls[carvechoice]; //chosen wall
                walls[carvechoice]= walls.back(); //replacing random choice with back element them popping back element in next line to effectively remove the chosen wall from the walls list as it is now going to be carved.
                walls.pop_back(); //swap and pop technique eliminates chosen wall from wall list as it has been chosen.

                int wallX = wallchoice.first; //setting coordinates of the randomly selected wall
                int wallY = wallchoice.second;
                
                for (int i = 0; i < directions.size(); i++) { //loop iterating through up, down, left, right options.
                    int nextX = wallX + directions[i].first / 2; //divide by 2 as we are finding the cells position relative from the position of the wall. The cell is immediately next to a wall and therefore we don't jump by 2 but by 1 and have to divide the direction vector by 2.
                    int nextY = wallY + directions[i].second / 2;

                    if (isValid(nextX,nextY, visitedcells)){ //checking next cells validity, because visitedcells prev passed by reference, isvalid is able to check any changes.
                        maze[nextX][nextY]=' '; //carving
                        maze[wallX][wallY]=' ';
                        visitedcells[nextX][nextY]=true; //add to visited list
                    }

                     for (int j = 0; j < directions.size(); j++) {
                         int nextWallX = nextX + directions[j].first;
                         int nextWallY = nextY + directions[j].second;
                         if (nextWallX > 0 && nextWallX < rows - 1 && nextWallY > 0 && nextWallY < cols - 1) {
                             walls.push_back({nextWallX, nextWallY});
                         }
                     }
                }
            }
           

            

            

        }
};



int main() {
    Maze gameMaze;
    gameMaze.initialisemaze();
    gameMaze.carve();
    gameMaze.displaymaze();

    return 0;  
}

