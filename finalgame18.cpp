#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
using namespace std;

fstream highscore;
int snakex[16] = {30};
int snakey[16] = {6};
int snakeLength = 1;

int foodx[15] = {20, 30, 40, 25, 35, 15, 16, 10, 25, 32, 40, 12, 6, 19, 9};
int foody[15] = {5, 10, 15, 12, 8, 6, 4, 11, 4, 11, 9, 5, 3, 10, 6};
int currentFood = 0;

void maze();
void xy(int x, int y);
void updateSnakePosition();
void printSnake();
void cutSnake();
void updateScoreAndLives();
char getCharAtxy(short int x, short int y);
void score();
void spawnFood();
bool checkWallCollision(int x, int y);

int scores = 0;
int life = 3;
int dx = 1, dy = 0;

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize = {1, 1};
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}
void highscores()
{
    highscore.open("snakescore.txt", ios::app);
    highscore << endl
              << scores;
    highscore.close();
}
void showscore()
{
    bool showhigh = true;
    int scoreslist;
    cout << "Scores: ";
    highscore.open("snakescore.txt", ios::in);
    // for (int i = 0; i < highscore.length(); i++)
    while (highscore >> scoreslist)
    {
        cout << endl
             << scoreslist;
        if (scores < scoreslist)
        {
            showhigh = false;
        }
    }
    highscore.close();
    if (showhigh)
    {
        cout << "----You have hit the high score----" << endl;
    }
}
void updateScoreAndLives()
{
    xy(0, 20);
    cout << "Score = " << scores << "  Lives = " << life << "   ";
}

void score()
{
    scores++;
    updateScoreAndLives();
}

void spawnFood()
{
    if (currentFood < 15)
    {
        xy(foodx[currentFood], foody[currentFood]);
        cout << ".";
    }
}

main()
{
    system("color 03");
    system("cls");
    maze();
    updateScoreAndLives();
    spawnFood();
    while (true)
    {
        Sleep(50);
        cutSnake();

        if (GetAsyncKeyState(VK_RIGHT) < 0)
        {
            dx = 1;
            dy = 0;
        }
        if (GetAsyncKeyState(VK_LEFT) < 0)
        {
            dx = -1;
            dy = 0;
        }
        if (GetAsyncKeyState(VK_UP) < 0)
        {
            dx = 0;
            dy = -1;
        }
        if (GetAsyncKeyState(VK_DOWN) < 0)
        {
            dx = 0;
            dy = 1;
        }
        int nextx = snakex[0] + dx;
        int nexty = snakey[0] + dy;

        if (checkWallCollision(nextx, nexty))
        {
            life--;
            updateScoreAndLives();

            if (life <= 0)
            {
                system("color 04");
                cout << "\n....GAME OVER!...." << endl;
                cout << " Final Score: " << scores;
                cout << endl;
                highscores();
                showscore();
                break;
            }

            snakex[0] = 30;
            snakey[0] = 6;
            // getch();
        }
        else
        {
            char nextPosition = getCharAtxy(nextx, nexty);
            if (nextPosition == ' ' || nextPosition == '.')
            {
                if (nextPosition == '.')
                {
                    score();
                    snakeLength++;
                    currentFood++;
                    spawnFood();
                }
                updateSnakePosition();
            }
        }
        printSnake();
        if (currentFood == 15)
        {
            system("color 02");
            xy(0, 20);
            cout << "\nYOU WIN! Final Score: " << scores;
            break;
        }
    }
    return 0;
}

void maze()
{
    cout << "#################################################################" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "##                                                             ##" << endl;
    cout << "#################################################################" << endl;
}

void xy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void updateSnakePosition()
{
    for (int i = snakeLength - 1; i > 0; i--)
    {
        snakex[i] = snakex[i - 1];
        snakey[i] = snakey[i - 1];
    }

    snakex[0] += dx;
    snakey[0] += dy;
}

void printSnake()
{
    for (int i = 0; i < snakeLength; i++)
    {
        xy(snakex[i], snakey[i]);
        cout << "S";
    }
}

void cutSnake()
{
    for (int i = 0; i < snakeLength; i++)
    {
        xy(snakex[i], snakey[i]);
        cout << " ";
    }
}

bool checkWallCollision(int x, int y)
{
    char nextPosition = getCharAtxy(x, y);
    if (nextPosition == '#')
    {
        system("color 04");
        Sleep(400);
        system("color 03");
        return true;
    }
    return false;
}
