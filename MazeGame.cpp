#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
using namespace std;

class Maze {
public:
    int enemy1X, enemy1Y;
    int enemy2X, enemy2Y;
    int enemy3X, enemy3Y;
    int playerX, playerY;
    int rows, cols;
    bool hasKey = false;

    vector<vector<char>> maze; //2d vector for maze
    vector<vector<bool>> visitedcells; //2d vector for visited cells

    Maze() {
        rows = 25; //maze dimensions
        cols = 25;
        maze.resize(rows, vector<char>(cols, '#'));
        visitedcells.resize(rows, vector<bool>(cols, false));

        enemy1X = enemy1Y = 0;  //player and enemy positions declared and initialised
        enemy2X = enemy2Y = 0;
        enemy3X = enemy3Y = 0;
        playerX = playerY = 0;
    }

    bool isValid(int x, int y, vector<vector<bool>>& visited) {  //check to see if the cell to be carved iw valid(boundary conditions met), visited list called by reference so it's current value can be checked
        return x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y];
    }

    void initialisemaze() { //iterates through rows and columns and initialises each cell with '#'s
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                maze[i][j] = '#';
                visitedcells[i][j] = false; //also initialises all visited cells to false, as none have been visited yet as carve() hasn't begun
            }
        }
    }

    void displaymaze() {  //displays maze
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << maze[i][j];
            }
            cout << endl;
        }
    }

    void randDirection(int directions[4][2]) {
        for (int i = 0; i < 4; i++) {
            int randomIndex = rand() % 4;


            int tempX = directions[i][0];  //replaces directions[i] with directions[randomIndex] creating random direction choice
            int tempY = directions[i][1];
            directions[i][0] = directions[randomIndex][0];
            directions[i][1] = directions[randomIndex][1];
            directions[randomIndex][0] = tempX;
            directions[randomIndex][1] = tempY;
        }
    }


    void carve(int x, int y) {
        visitedcells[x][y] = true; //cell is visited
        maze[x][y] = ' '; //cell is visited and carved so now must be cleared

        int directions[4][2] = { //list of directions to carve in, done in 2's to see if cell across the wall to be carved is valid
            {-2, 0},
            {2, 0},
            {0, -2},
            {0, 2}
        };

        randDirection(directions); //random direction selected

        for (int i = 0; i < 4; i++) {
            int newx = x + directions[i][0]; //x value of cell across the wall to be carved
            int newy = y + directions[i][1]; //y value of cell across the wall to be carved

            if (newx > 0 && newx < rows - 1 && newy > 0 && newy < cols - 1) { //checks to see if cell across wall to be carved is valid, if it is, the wall in the middle is carved
                if (!visitedcells[newx][newy]) {
                    int midX = (x + newx) / 2;
                    int midY = (y + newy) / 2;
                    maze[midX][midY] = ' '; //new carved cell cleared

                    carve(newx, newy); //repeats
                }
            }
        }
    }

    void placeCharacters() {

        playerX = 1;
        playerY = 1;
        maze[playerX][playerY] = 'P'; //player in top left indicated by 'P'


        enemy1X = rows - 2;
        enemy1Y = cols - 2;
        maze[enemy1X][enemy1Y] = 'E';


        enemy2X = 3;
        enemy2Y = cols - 2;
        maze[enemy2X][enemy2Y] = 'E';


        enemy3X = rows - 2;
        enemy3Y = 1;
        maze[enemy3X][enemy3Y] = 'E';
    }

    void moveEnemy1() {
        int enemydirection = (rand() % 4) + 1; //random number from 1 to 4 picked

        if (enemy1X == playerX && enemy1Y == playerY) {
            cout << "An enemy caught you! Game Over.\n";
            Sleep(2000); //sleep used to give player time to read message before game closes
            exit(0);
        }

        switch (enemydirection) {
        case 1:
            if ((maze[enemy1X - 1][enemy1Y] != '#') &&
                ((enemy1X - 1) >= 0) &&
                (maze[enemy1X - 1][enemy1Y] != 'K') &&
                (maze[enemy1X - 1][enemy1Y] != 'D'))
            {
                maze[enemy1X][enemy1Y] = ' ';
                enemy1X--;
                maze[enemy1X][enemy1Y] = 'E';
            }
            break; //so not all cases are executed, only the one that applies
        case 2:
            if ((maze[enemy1X + 1][enemy1Y] != '#') &&
                ((enemy1X + 1) < rows) &&
                (maze[enemy1X + 1][enemy1Y] != 'K') &&
                (maze[enemy1X + 1][enemy1Y] != 'D'))
            {
                maze[enemy1X][enemy1Y] = ' ';
                enemy1X++;
                maze[enemy1X][enemy1Y] = 'E';
            }
            break;
        case 3:
            if ((maze[enemy1X][enemy1Y - 1] != '#') &&
                ((enemy1Y - 1) >= 0) &&
                (maze[enemy1X][enemy1Y - 1] != 'K') &&
                (maze[enemy1X][enemy1Y - 1] != 'D'))
            {
                maze[enemy1X][enemy1Y] = ' ';
                enemy1Y--;
                maze[enemy1X][enemy1Y] = 'E';
            }
            break;
        case 4:
            if ((maze[enemy1X][enemy1Y + 1] != '#') &&
                ((enemy1Y + 1) < cols) &&
                (maze[enemy1X][enemy1Y + 1] != 'K') &&
                (maze[enemy1X][enemy1Y + 1] != 'D'))
            {
                maze[enemy1X][enemy1Y] = ' ';
                enemy1Y++;
                maze[enemy1X][enemy1Y] = 'E';
            }
            break;
        }


    }

    void moveEnemy2() {
        int enemydirection2 = (rand() % 4) + 1;

        if (enemy2X == playerX && enemy2Y == playerY) {
            cout << "An enemy caught you! Game Over.\n";
            Sleep(2000);
            exit(0);
        }

        switch (enemydirection2) {
        case 1:
            if ((maze[enemy2X - 1][enemy2Y] != '#') &&
                ((enemy2X - 1) >= 0) &&
                (maze[enemy2X - 1][enemy2Y] != 'K') &&
                (maze[enemy2X - 1][enemy2Y] != 'D'))
            {
                maze[enemy2X][enemy2Y] = ' ';
                enemy2X--;
                maze[enemy2X][enemy2Y] = 'E';
            }
            break;
        case 2:
            if ((maze[enemy2X + 1][enemy2Y] != '#') &&
                ((enemy2X + 1) < rows) &&
                (maze[enemy2X + 1][enemy2Y] != 'K') &&
                (maze[enemy2X + 1][enemy2Y] != 'D'))
            {
                maze[enemy2X][enemy2Y] = ' ';
                enemy2X++;
                maze[enemy2X][enemy2Y] = 'E';
            }
            break;
        case 3:
            if ((maze[enemy2X][enemy2Y - 1] != '#') &&
                ((enemy2Y - 1) >= 0) &&
                (maze[enemy2X][enemy2Y - 1] != 'K') &&
                (maze[enemy2X][enemy2Y - 1] != 'D'))
            {
                maze[enemy2X][enemy2Y] = ' ';
                enemy2Y--;
                maze[enemy2X][enemy2Y] = 'E';
            }
            break;
        case 4:
            if ((maze[enemy2X][enemy2Y + 1] != '#') &&
                ((enemy2Y + 1) < cols) &&
                (maze[enemy2X][enemy2Y + 1] != 'K') &&
                (maze[enemy2X][enemy2Y + 1] != 'D'))
            {
                maze[enemy2X][enemy2Y] = ' ';
                enemy2Y++;
                maze[enemy2X][enemy2Y] = 'E';
            }
            break;
        }
    }


    void moveEnemy3() {
        int enemydirection3 = (rand() % 4) + 1;

        if (enemy3X == playerX && enemy3Y == playerY) {
            cout << "An enemy caught you! Game Over.\n";
            Sleep(2000);
            exit(0);
        }

        switch (enemydirection3) {
        case 1:
            if ((maze[enemy3X - 1][enemy3Y] != '#') &&
                ((enemy3X - 1) >= 0) &&
                (maze[enemy3X - 1][enemy3Y] != 'K') &&
                (maze[enemy3X - 1][enemy3Y] != 'D'))
            {
                maze[enemy3X][enemy3Y] = ' ';
                enemy3X--;
                maze[enemy3X][enemy3Y] = 'E';
            }
            break;
        case 2:
            if ((maze[enemy3X + 1][enemy3Y] != '#') &&
                ((enemy3X + 1) < rows) &&
                (maze[enemy3X + 1][enemy3Y] != 'K') &&
                (maze[enemy3X + 1][enemy3Y] != 'D'))
            {
                maze[enemy3X][enemy3Y] = ' ';
                enemy3X++;
                maze[enemy3X][enemy3Y] = 'E';
            }
            break;
        case 3:
            if ((maze[enemy3X][enemy3Y - 1] != '#') &&
                ((enemy3Y - 1) >= 0) &&
                (maze[enemy3X][enemy3Y - 1] != 'K') &&
                (maze[enemy3X][enemy3Y - 1] != 'D'))
            {
                maze[enemy3X][enemy3Y] = ' ';
                enemy3Y--;
                maze[enemy3X][enemy3Y] = 'E';
            }
            break;
        case 4:
            if ((maze[enemy3X][enemy3Y + 1] != '#') &&
                ((enemy3Y + 1) < cols) &&
                (maze[enemy3X][enemy3Y + 1] != 'K') &&
                (maze[enemy3X][enemy3Y + 1] != 'D'))
            {
                maze[enemy3X][enemy3Y] = ' ';
                enemy3Y++;
                maze[enemy3X][enemy3Y] = 'E';
            }
            break;
        }

    }


    
    void movePlayer() {

        char playerdirection = _getch();
        while (!(playerdirection == 'W' || playerdirection == 'S' || //checking for valid input
            playerdirection == 'A' || playerdirection == 'D' ||
            playerdirection == 'w' || playerdirection == 's' ||
            playerdirection == 'a' || playerdirection == 'd'))
        {
            cout << "Please enter a valid move.\n";
            playerdirection = _getch();
        }


        maze[playerX][playerY] = ' '; //clear old positon

        int newX = playerX;
        int newY = playerY;

        if ((playerdirection == 'W' || playerdirection == 'w') && playerX > 0) {
            newX = playerX - 1;
            newY = playerY;
        }
        else if ((playerdirection == 'S' || playerdirection == 's') && playerX < rows - 1) {
            newX = playerX + 1;
            newY = playerY;
        }
        else if ((playerdirection == 'A' || playerdirection == 'a') && playerY > 0) {
            newX = playerX;
            newY = playerY - 1;
        }
        else if ((playerdirection == 'D' || playerdirection == 'd') && playerY < cols - 1) {
            newX = playerX;
            newY = playerY + 1;
        }


        char nextCell = maze[newX][newY]; //used to check next cell


        if (nextCell == '#') {
            maze[playerX][playerY] = 'P';
            return;
        }

        if (nextCell == 'D' && !hasKey) {
            maze[playerX][playerY] = 'P'; //player can't move through door without key
            cout << "Access Denied! \n";
            return;
        }


        if ((playerX == enemy1X && playerY == enemy1Y) || //if player and enemy are in same cell, game over
            (playerX == enemy2X && playerY == enemy2Y) ||
            (playerX == enemy3X && playerY == enemy3Y)) {
            cout << "An enemy caught you! Game Over.\n";
            Sleep(2000);
            exit(0);
        }

        playerX = newX; //if none of these are met, player can move
        playerY = newY;
        maze[playerX][playerY] = 'P';
    }
    void puzzle() {

        maze[1][23] = 'K'; //key and door placed
        maze[24][1] = 'D';

        if (playerX == 1 && playerY == 23) { //if player standing on key, haskey is true
            hasKey = true;
            cout << "You have found the key!\n";
        }

        if (hasKey == true) { //if haskey true, key is cleared
            maze[1][23] = ' ';
        }


        if ((maze[playerX][playerY] == maze[24][1]) && hasKey) { //if player stands on door and has the key, game is won
            cout << "Congratulations, you have escaped the maze!\n";
            exit(0);
        }
    }
};

int main() {
    srand(time(0)); //random seed
    Maze gameMaze; //Maze class object created
    gameMaze.initialisemaze(); //object used to call functions from Maze class

    gameMaze.carve(1, 1); //once initialised, maze is carved

    gameMaze.placeCharacters(); //place the characters

    gameMaze.puzzle(); //puzzle and door are placed after maze is carved to ensure they aren't carved over, same goes for player and enemies

    system("cls"); //clears screen

    while (true) { //game loop

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //used to move cursor to top left of console
        COORD Position = { 0, 0 }; //position of cursor
        SetConsoleCursorPosition(hOut, Position); //these lines are to stop maze from scrolling
        //these commands are from <windows.h> library

        gameMaze.displaymaze(); //maze is displayed


        gameMaze.movePlayer();


        gameMaze.moveEnemy1();
        gameMaze.moveEnemy2();
        gameMaze.moveEnemy3();


        gameMaze.puzzle();

        Sleep(100); //screen refresh rate
    }

    return 0;
}
