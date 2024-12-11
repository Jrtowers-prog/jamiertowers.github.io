#include <iostream>
#include <string>
#include <windows.h>
#include <chrono>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<char>> maze; //delcaring global 2d vector to store map

class Maze {

    public:
        int enemyX, enemyY;
        int playerX, playerY;
        int rows = 15; //dimensions
        int cols = 15;
        
        void initialisemaze() {
            maze.resize(rows,vector<char>(cols, '#')); //initialises maze with dimensions cols and rows, also fills with #'s so that the carving algorithm works
            playerX = 1;
            playerY = 1;
            maze[playerX][playerY] = 'P'; //player's initial position indicated by P icon
        }

        void displaymaze(){
            for (int i=0; i < rows; i++){
                for (int j=0; j < cols; j++){
                    cout << maze[i][j];
                }
                cout << endl;
            }
        };
        void moveEnemy(){
          int enemydirection = (rand() % 4)+1;
          switch (enemydirection) {
            case 1:
              if ((maze[enemyX-1][enemyY] != '#') && ((enemyX-1) >= 0)))
                maze[enemyX][enemyY] = ' ';
                enemyX--;
                maze[enemyX][enemyY] = 'E';
            case 2:
              if ((maze[enemyX+1][enemyY] != '#') && ((enemyX+1) < rows)))
                maze[enemyX][enemyY] = ' ';
                enemyX++;
                maze[enemyX][enemyY] = 'E';
            case 3:
              if ((maze[enemyX][enemyY-1] != '#') && ((enemyY-1) >= 0)))
                maze[enemyX][enemyY] = ' ';
                enemyY--;
                maze[enemyX][enemyY] = 'E';
            case 4:
              if ((maze[enemyX][enemyY+1] != '#') && ((enemyX-1) < cols)))
                maze[enemyX][enemyY] = ' ';
                enemyY++;
                maze[enemyX][enemyY] = 'E';
          }
        }
        void movePlayer(){
            char playerdirection;
            cin >> playerdirection;
            while (!(playerdirection == 'W' ||playerdirection == 'S' ||playerdirection == 'A' ||playerdirection == 'D' ||playerdirection == 'w' ||playerdirection == 's' ||playerdirection == 'a' ||playerdirection == 'd')){
                cout << "Please enter a valid move.";
                cin >> playerdirection;
            }
            maze[playerX][playerY] = ' ';
            if ((playerdirection == 'W'||playerdirection == 'w') && (maze[playerX-1][playerY] != '#') && ((playerX-1) >= 0)){
                playerX--;
                maze[playerX][playerY]='P';
            }
            if ((playerdirection == 'S'||playerdirection == 's') && (maze[playerX+1][playerY] != '#') && ((playerX+1) < rows)){
                playerX++;
                maze[playerX][playerY]='P';
            }
            if ((playerdirection == 'A'||playerdirection == 'a') && (maze[playerX][playerY-1] != '#') && ((playerY-1) >= 0)){
                playerY--;
                maze[playerX][playerY]='P';
            }
            if ((playerdirection == 'D'||playerdirection == 'd') && (maze[playerX][playerY+1] != '#') && ((playerY+1) < cols)){
                playerY++;
                maze[playerX][playerY]='P';
            }

        }
        
        void carve ();

};



class Enemy {
    public:
        char enemystart();
        char moveenemy();
};

class Puzzle {
    public:
        char placekey();
        char placedoor();
        bool haskey();

};

int main() {
    void initialisemaze();

return 0;  
}


