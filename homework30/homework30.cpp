// homework30.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <random>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
using namespace std;

// Console colors
enum ConsoleColor {
	// Standard text colors
	GRAY = 8, BLUE, GREEN,
	TEAL, RED, PINK,
	YELLOW, WHITE,
	// Faded text colors
	BLACK = 0, BLUE_FADE, GREEN_FADE,
	TEAL_FADE, RED_FADE, PINK_FADE,
	YELLOW_FADE, WHITE_FADE,
};
void SetColor(ConsoleColor text, ConsoleColor background = BLACK)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (short)text | ((short)background << 4));
}
void SetColor(short text, short background = BLACK)
{
	SetColor((ConsoleColor)text, (ConsoleColor)background);
}
void ResetColor()
{
	SetColor(WHITE, BLACK);
}
void SetCursorPosition(short x, short y) //#include <Windows.h>
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
enum Keys {
	ESC = 27, ARROW_START = 224, ENTER = 13,
	UP_ARROW = 72, DOWN_ARROW = 80, LEFT_ARROW = 75, RIGHT_ARROW = 77
};


const int SIZE_ARR = 4;
void fillArrayUniqueRandom(int arr[SIZE_ARR][SIZE_ARR], int start, int end);
int getRandNumber(int start, int end);
void printField(int field[SIZE_ARR][SIZE_ARR]);
void printField(int field[SIZE_ARR][SIZE_ARR], int fontColor, int backColor, int counter);
int userInput();
void swapNumber(int arr[SIZE_ARR][SIZE_ARR], int key);
bool isArraySorted(int arr[SIZE_ARR][SIZE_ARR]);

int main()
{
	srand(time(0));

	int arr[SIZE_ARR][SIZE_ARR] = { 
		{7,6,2,4}, 
		{5,13,15,9}, 
		{3,14,1,10},
		{12,11,8,0} 
	};

	/*int arr[SIZE_ARR][SIZE_ARR];
	fillArrayUniqueRandom(arr, 1, 15);*/
	ResetColor();
	cout << "Welcome to the puzzle\n" << "Move numbers below in order of increasing\n" 
		<< "Use arrow keys to move numbers\n";
	printField(arr);
	cout << endl;
	int choice;

	do
	{
		choice = userInput();
		swapNumber(arr, choice);
	} while (!isArraySorted(arr));
	SetCursorPosition(15, 23);
	printField(arr, 15,0,0);
	ResetColor();
	cout << "\nCONGRATS! You solved the puzzle\n";
	
}

void fillArrayUniqueRandom(int arr[SIZE_ARR][SIZE_ARR], int start, int end)
{
	int counter = 0;
	//int testInt = 0;
	//int testInt2 = 0;
	for (int i = 0; i < SIZE_ARR; ++i)
	{
		for (int j = 0; j < SIZE_ARR; ++j)
		{
			arr[i][j] = getRandNumber(start, end);
			//testInt = arr[i][j];
			for (int y = counter - 1; y >= 0; --y)
			{
				if (i == j and i == SIZE_ARR - 1)
				{
					arr[i][j] = 0;
					break;
				}
				if (arr[i][j] == arr[0][y])
				{
					arr[i][j] = getRandNumber(start, end);
					//testInt2 = arr[i][j];
					y = counter;
				}
			}
			counter++;
		}
	}
}

int getRandNumber(int start, int end)
{
	int randomNumber;
	randomNumber = start + rand() % ((end + 1) - start);
	return randomNumber;
}

void printField(int field[SIZE_ARR][SIZE_ARR])
{
	SetColor(ConsoleColor::BLUE, ConsoleColor::WHITE);

	for (int i = 0; i < SIZE_ARR; ++i) {
		for (int j = 0; j < SIZE_ARR; ++j) {
			SetCursorPosition(3 + j * 6, (4 + i * 2));
			if (field[i][j] == 0)
			{
				SetColor(ConsoleColor::BLACK, ConsoleColor::BLACK);
			}
			cout << " " << field[i][j];
			cout << ((field[i][j]<10)? ("  ") : (" "));
			SetColor(ConsoleColor::BLUE, ConsoleColor::WHITE);
		}
		cout << endl;
	}
	ResetColor();
}

void printField(int field[SIZE_ARR][SIZE_ARR], int fontColor, int backColor, int counter)
{
	SetColor(fontColor, backColor);
	for (int i = 0; i < SIZE_ARR; ++i) {
		for (int j = 0; j < SIZE_ARR; ++j) {
			SetCursorPosition(3 + j * 6, (4 + i * 2));
			if (field[i][j] == 0)
			{
				SetColor(ConsoleColor::BLACK, ConsoleColor::BLACK);
			}
			cout << " " << field[i][j];
			cout << ((field[i][j] < 10) ? ("  ") : (" "));
			SetColor(fontColor, backColor);
		}
		cout << endl;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(400));
	if (counter < 16)
	{
		printField(field, fontColor - 1, backColor + 1, counter + 1);
	}
	
}

int userInput()
{
	int key = 0;
	//cout << endl;
	//cout << "Use arrow keys to move numbers\n";
	bool keybInputWait = true;
	SetCursorPosition(35, 5);
	
	while (keybInputWait)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == UP_ARROW)
			{
				cout << "PRESSED KEY -> UP ARROW" << endl;
				keybInputWait = false;
				return key;
			}
			else if (key == DOWN_ARROW)
			{
				cout << "PRESSED KEY -> DOWN ARROW" << endl;
				keybInputWait = false;
				return key;
			}
			else if (key == RIGHT_ARROW)
			{
				cout << "PRESSED KEY -> RIGHT ARROW" << endl;
				keybInputWait = false;
				return key;
			}
			else if (key == LEFT_ARROW)
			{
				cout << "PRESSED KEY -> LEFT ARROW" << endl;
				keybInputWait = false;
				return key;
			}
		}
	}
	return key;
}

void swapNumber(int arr[SIZE_ARR][SIZE_ARR], int key)
{
	int rowIdx;
	int colIdx;
	bool isEmptyFound = false;

	for (int row = 0; row < SIZE_ARR; ++row)       // searching an empty cell in array (0 as empty)
	{
		for (int col = 0; col < SIZE_ARR; ++col)
		{
			if (arr[row][col] == 0)
			{
				rowIdx = row;
				colIdx = col;
				//cout << "row = " << rowIdx << " col = " << colIdx << endl;
				break;
			}
		}
		if (isEmptyFound) break;
	}

	// conditions not to get values outside of an array
	bool upArrowActive = !(rowIdx == (SIZE_ARR - 1));
	bool downArrowActive = !(rowIdx == 0);
	bool leftArrowActive = !(colIdx == (SIZE_ARR - 1));
	bool rightArrowActive = !(colIdx == 0);

	if (key == UP_ARROW and upArrowActive)
	{
		swap(arr[rowIdx][colIdx], arr[rowIdx + 1][colIdx]);
	}
	else if (key == DOWN_ARROW and downArrowActive)
	{
		swap(arr[rowIdx][colIdx], arr[rowIdx - 1][colIdx]);
	}
	else if (key == RIGHT_ARROW and rightArrowActive)
	{
		swap(arr[rowIdx][colIdx], arr[rowIdx][colIdx - 1]);
	}
	else if (key == LEFT_ARROW and leftArrowActive)
	{
		swap(arr[rowIdx][colIdx], arr[rowIdx][colIdx + 1]);
	}

	printField(arr);

}

bool isArraySorted(int arr[SIZE_ARR][SIZE_ARR])
{
	for (int i = 0; i < (SIZE_ARR * SIZE_ARR) - 1; ++i)
	{
		for (int j = i; j < (SIZE_ARR * SIZE_ARR) - 1; ++j)
		{
			if (arr[0][i] > arr[0][j]) return false;
		}
	}
	return true;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
