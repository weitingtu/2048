#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>   

//Copy the content of src to dst
void CopyBoard(int dst[4][4], int src[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dst[i][j] = src[i][j];
		}
	}
}

//return 1 if the contents of b1 and b2 are the same
//return 0 otherwise
int AreEqual(int b1[4][4], int b2[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b1[i][j] != b2[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

void PrintBoard(int board[4][4]) {
	for (int y = 0; y < 17; y++) {
		if (y % 4 == 0) {
			printf("*****************************\n");
		}
		else if (y % 4 == 1 || y % 4 == 3) {
			printf("*      *      *      *      *\n");
		}
		else {
			int i = y / 4;
			for (int j = 0; j < 4; j++) {
				printf("*");

				if (board[i][j] == 0) {
					printf("      ");
				}
				else if (board[i][j] < 10) {
					printf("   %d  ", board[i][j]);
				}
				else if (board[i][j] < 100) {
					printf("  %d  ", board[i][j]);
				}
				else if (board[i][j] < 1000) {
					printf("  %d ", board[i][j]);
				}
				else {
					printf(" %d ", board[i][j]);
				}
			}
			printf("*\n");
		}
	}

	return;
}

//print the old board, the action, and the new board
void PrintGame(int oldBoard[4][4], int newBoard[4][4], char a) {
	PrintBoard(oldBoard);
	if (a == 'w') {
		printf("\n\nUp\n\n");
	}
	else if (a == 's') {
		printf("\n\nDown\n\n");
	}
	else if (a == 'd') {
		printf("\n\nRight\n\n");
	}
	else if (a == 'a') {
		printf("\n\nLeft\n\n");
	}
	PrintBoard(newBoard);
}

//return the number of 0s in the board
int GetNEmptyPos(int b[4][4]) {
	int count = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b[i][j] == 0) {
				count++;
			}
		}
	}

	return count;
}

int GenNewNumber() {
	//return 2 with prob 0.9
	//return 1 with prob 0.1
	/*****************************/
	/****                     ****/
	/****                     ****/
	/**** YOUR CODE GOES HERE ****/
	/****                     ****/
	/****                     ****/
	/*****************************/
	double p = (double)rand() / (RAND_MAX + 1.0);
	if (p < 0.9)
		return 2;
	return 4;
}

void InitBoard(int board[4][4]) {
	int initCol1, initRow1, initCol2, initRow2;
	initCol1 = rand() % 4;
	initRow1 = rand() % 4;

	initCol2 = rand() % 4;
	initRow2 = rand() % 4;

	while (initCol1 == initCol2 && initRow1 == initRow2) {
		initCol2 = rand() % 4;
		initRow2 = rand() % 4;
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}

	board[initCol1][initRow1] = GenNewNumber();
	board[initCol2][initRow2] = GenNewNumber();

	return;
}


void UpdateIthColumn(int board[4][4], int i, char a) {
	//update the ith col (i = 0,1,2, or 3) with action a (a == 'w' or 's')
	/*****************************/
	/****                     ****/
	/****                     ****/
	/**** YOUR CODE GOES HERE ****/
	/****                     ****/
	/****                     ****/
	/*****************************/
	if ('w' == a)
	{
		// move up
		int merge = 0;
		for (int j = 1; j < 4; j++)
		{
			if (0 == board[j][i])
			{
				continue;
			}
			int k = j;
			int l = j - 1;
			while (l >= 0)
			{
				if (0 == board[l][i])
				{
					board[l][i] = board[k][i];
					board[k][i] = 0;
					--k;
					--l;
				}
				else if (0 == merge && board[l][i] == board[k][i])
				{
					merge = 1;
					board[l][i] = 2 * board[k][i];
					board[k][i] = 0;
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
	else if ('s' == a)
	{
		// move down
		int merge = 0;
		for (int j = 2; j >= 0; --j)
		{
			if (0 == board[j][i])
			{
				continue;
			}
			int k = j;
			int l = j + 1;
			while (l < 4)
			{
				if (0 == board[l][i])
				{
					board[l][i] = board[k][i];
					board[k][i] = 0;
					++k;
					++l;
				}
				else if (0 == merge && board[l][i] == board[k][i])
				{
					merge = 1;
					board[l][i] = 2 * board[k][i];
					board[k][i] = 0;
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
}

void UpdateIthRow(int board[4][4], int i, char a) {
	//update the ith row (i = 0,1,2, or 3) with action a (a == 'a' or 'd')
	/*****************************/
	/****                     ****/
	/****                     ****/
	/**** YOUR CODE GOES HERE ****/
	/****                     ****/
	/****                     ****/
	/*****************************/
	if ('a' == a)
	{
		// move left
		int merge = 0;
		for (int j = 1; j < 4; j++)
		{
			if (0 == board[i][j])
			{
				continue;
			}
			int k = j;
			int l = j - 1;
			while (l >= 0)
			{
				if (0 == board[i][l])
				{
					board[i][l] = board[i][k];
					board[i][k] = 0;
					--k;
					--l;
				}
				else if (0 == merge && board[i][l] == board[i][k])
				{
					merge = 1;
					board[i][l] = 2 * board[i][k];
					board[i][k] = 0;
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
	else if ('d' == a)
	{
		// move right
		int merge = 0;
		for (int j = 2; j >= 0; --j)
		{
			if (0 == board[i][j])
			{
				continue;
			}
			int k = j;
			int l = j + 1;
			while (l < 4)
			{
				if (0 == board[i][l])
				{
					board[i][l] = board[i][k];
					board[i][k] = 0;
					++k;
					++l;
				}
				else if (0 == merge && board[i][l] == board[i][k])
				{
					merge = 1;
					board[i][l] = 2 * board[i][k];
					board[i][k] = 0;
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
}


int IsGameOver(int board[4][4]) {
	//return 0; //initially, simply return 0 so that the game always continues

	//return 1 if the game is over
	//return 0 otherwise
	/*****************************/
	/****                     ****/
	/****                     ****/
	/**** YOUR CODE GOES HERE ****/
	/****                     ****/
	/****                     ****/
	/*****************************/
	int over = 1;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (0 == board[i][j])
			{
				over = 0;
				break;
			}
			int k = i;
			int l = j - 1;
			if (k >= 0 && k < 4 && l >= 0 && l < 4 && board[i][j] == board[k][l])
			{
				over = 0;
				break;
			}

			k = i;
			l = j + 1;
			if (k >= 0 && k < 4 && l >= 0 && l < 4 && board[i][j] == board[k][l])
			{
				over = 0;
				break;
			}

			k = i - 1;
			l = j;
			if (k >= 0 && k < 4 && l >= 0 && l < 4 && board[i][j] == board[k][l])
			{
				over = 0;
				break;
			}

			k = i + 1;
			l = j;
			if (k >= 0 && k < 4 && l >= 0 && l < 4 && board[i][j] == board[k][l])
			{
				over = 0;
				break;
			}
		}
		if (0 == over)
		{
			break;
		}
	}
	return over;
}

void UpdateBoard(int board[4][4], char a) {
	if (a == 'w' || a == 's') {
		for (int i = 0; i < 4; i++) {
			UpdateIthColumn(board, i, a);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			UpdateIthRow(board, i, a);
		}
	}
	return;
}

//add a new number (by calling GenNewNumber()) to an empty slot
void AddNewNumber(int board[4][4]) {
	int nEmptyPos = GetNEmptyPos(board);

	int r = 1 + rand() % nEmptyPos; // generate a random number between 1 and nEmptyPos
	//add a new number to the rth empty slot
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				r--;
				if (r == 0) {
					board[i][j] = GenNewNumber();
					break;
				}
			}
		}
	}
}

int main() {
	int board[4][4];
	int oldBoard[4][4];
	//srand(time(NULL));
	srand(0);
	InitBoard(board);
	PrintBoard(board);

	for (;;) {
		char c = _getch();
		if (c != 'w' && c != 's' && c != 'a' && c != 'd') {
			printf("\n\n please press w, s, a, or d\n");
			continue;
		}
		CopyBoard(oldBoard, board);
		UpdateBoard(board, c);

		//if the action is valid, i.e., the board is updated (changed), add a new number
		if (!AreEqual(board, oldBoard)) {
			AddNewNumber(board);
			system("cls"); // clear the screen
			PrintGame(oldBoard, board, c);
		}

		//if the game is over after the move, print game over
		if (IsGameOver(board)) {
			printf("\n\n Game Over!!\n\n");
			getchar();
		}
	}

	return 0;
}
