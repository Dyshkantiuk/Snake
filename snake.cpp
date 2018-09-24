#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);   // need for change color;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int color = 1;
int hi = 0;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup();
void Draw();
void Logic();
void DrawLose();
void Input();

int main() {
	srand(time(NULL));
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		if (gameOver == true) {
			DrawLose();
			nTail = 0;
			score = 0;
			_getch();
			switch (_getch())
			{
			case 'c':
				gameOver = false; break;
			case 'x':
				gameOver = true;  break;
				system("cls");
			}
		}
	}
	return 0;
}

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;          //start position snake
	y = height / 2;
	fruitX = width / 4;      //start position fruct
	fruitY = height / 4;
	score = 0;
}

void Draw() {
	Sleep(200);              //speed of game
	system("cls");
	for (int i = 0; i <= width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width + 1; j++) {
			if (j == 0 || j == width + 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
			{
				SetConsoleTextAttribute(hConsole, color);  // change color
				cout << "F";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						if (color != 1)
							SetConsoleTextAttribute(hConsole, color - 1);
						else SetConsoleTextAttribute(hConsole, 15);
						cout << "o";
						SetConsoleTextAttribute(hConsole, 15);
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i <= width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Highest: " << hi << "  Score: " << score << endl;
}

void Input() {          
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			if (dir != RIGHT || nTail == 0)dir = LEFT; break;
		case 'd':
			if (dir != LEFT || nTail == 0) dir = RIGHT; break;
		case 'w':
			if (dir != DOWN || nTail == 0) dir = UP; break;
		case 's':
			if (dir != UP || nTail == 0) dir = DOWN; break;
		case 'q':
			dir = STOP; break;
		case 'c':
			gameOver = false; break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i <= nTail; i++) {  // tail of snake
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)    // control
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
	}


	if (x > width)             // movement through the walls
		x = 0;
	else if (x < 0)
		x = width;
	if (y > height)
		y = 0;
	else if (y < 0)
		y = height;

	for (int i = 0; i < nTail; i++) {            //collision with tail
		if (tailX[i] == x && tailY[i] == y) {
			cout << "\a";
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) { 
		score += 5;
		if (hi < score) hi = score;
		fruitX = rand() % width;           // fruit position
		fruitY = rand() % height;
		nTail++;
		color++;
		if (color > 13) color = 1;
	}
}


void DrawLose() {                      // show menu
	system("cls");
	for (int i = 0; i <= width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height / 2 - 1; i++)
	{
		cout << "#";
		for (int j = 0; j <= width; j++)
			cout << " ";
		cout << "#" << endl;
	}

	cout << "#      You lose!      #" << endl;
	cout << "# For continue:       #" << endl;
	cout << "#          double \"c\" #" << endl;
	cout << "# For quite:          #" << endl;
	cout << "#          double \"x\" #" << endl;

	for (int i = 0; i < height / 2 - 3; i++)
	{
		cout << "#";
		for (int j = 0; j <= width; j++)
			cout << " ";
		cout << "#" << endl;
	}

	for (int i = 0; i <= width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Highest: " << hi << "  Score: " << score << endl;
}