#include <iostream>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <chrono>
#pragma comment(lib,"winmm.lib")

using namespace std;
bool gameOver;
int ob;
bool restart;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int nobs;
int obsX[100], obsY[100];
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    nobs = 0;
    restart = false;
}
void Draw()
{
    system("cls");
    for (int i = 0; i < width + 2;i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < height;i++)
    {
        for (int j = 0; j < width;j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                bool print1 = false;
                for (int k = 0;k < nobs;k++)
                {
                    if (obsX[k] == j && obsY[k] == i)
                    {
                        cout << "X";
                        print1 = true;
                    }
                }
                for (int k = 0; k < nTail;k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print && !print1)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2;i++)
        cout << "#";
    cout << endl;

}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1;i < nTail;i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    if (ob == 1) {
        for (int i = 0; i < nobs;i++)
        {
            obsX[i] = rand() % width;
            obsY[i] = rand() % height;
        }
        ob = 0;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;
    for (int i = 0;i < nTail;i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    for (int i = 0; i < nobs; i++)
        if (obsX[i] == x && obsY[i] == y)
            gameOver = true;
    if (x == fruitX && y == fruitY)
    {
        ob = 1;
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
        nobs++;
    }
}
int main()
{
    while (1) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        Setup();
        PlaySound(TEXT("C:\\Users\\User\\source\\repos\\Project16\\bgm.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        while (!restart) {
            system("cls");
            std::cout << "You have survived for " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
            cout << "Score:" << score << endl;
            cout << "Press R to restart" << endl;
            cout << "Press X to exit";
            if (_kbhit())
            {
                switch (_getch())
                {
                case 'r':
                    gameOver = false;
                    restart = true;
                    break;
                case 'x':
                    return 0;
                    break;
                }
            }
        }

    }

}
