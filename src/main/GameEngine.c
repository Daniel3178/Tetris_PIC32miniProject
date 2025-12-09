#include "TetrisGeneral.h"
#include "pic32max.h"

unsigned char tetrisField[32][128];
unsigned char rotated9x9Matrix[9][9];
unsigned char rotated12x12Matrix[12][12];
unsigned char isGameActive = FALSE;
unsigned char spawnCurrentOnce = FALSE;
unsigned char level = 1;
int currentScore = 0;

#pragma region COLLISION &FETCH

int DoesFit(Tetromino myTetromino)
{
	int i;
	int j;
	for (i = 0; i < myTetromino.width; i++)
	{
		for (j = 0; j < myTetromino.width; j++)
		{ /*If both the tetromino and the position of tetromino in the game fields are 1 then it doesn't fit */
			if (tetrisField[myTetromino.y + i][myTetromino.x + j] && *((myTetromino.matrix + i * myTetromino.width) + j))
			{
				return 0;
			}
		}
	}
	return 1;
}

void WriteToTetrisField()
{
	int i;
	int j;
	for (i = 0; i < currentTetromino.width; i++)
	{
		for (j = 0; j < currentTetromino.width; j++)
		{
			if (*((currentTetromino.matrix + i * currentTetromino.width) + j))
			{
				tetrisField[currentTetromino.y + i][currentTetromino.x + j] = *((currentTetromino.matrix + i * currentTetromino.width) + j);
			}
		}
	}
}

#pragma endregion

#pragma region SPAWNER
void SpawnNewTet()
{
	if (!spawnCurrentOnce)
	{
		currentTetromino = tetCollection[Rand() % 7];
		currentTetromino.x = 115;
		currentTetromino.y = 7;
	}
	if (spawnCurrentOnce)
	{
		currentTetromino = nextTetromino;
	}
	if (!DoesFit(currentTetromino))
	{
		isGameActive = FALSE;
	}
	nextTetromino = tetCollection[Rand() % 7];
	nextTetromino.x = 115;
	nextTetromino.y = 7;
	spawnCurrentOnce = TRUE;
}

#pragma endregion

#pragma region ROTATION
void Rotate9x9matrix(unsigned char *aMatrixToRotate, int aDirection)
{
	int i;
	int j;

	unsigned char tempArray[9][9];
	if (aDirection)
	{ // COUNTERCLOCKWISE ROTATION

		for (i = 0; i < 9; i++)
		{
			for (j = 8; j >= 0; j--)
			{
				tempArray[j][i] = *aMatrixToRotate++;
			}
		}
	}

	else
	{ // CLOCKWISE ROTATION

		for (i = 8; i >= 0; i--)
		{
			for (j = 0; j < 9; j++)
			{
				tempArray[j][i] = *aMatrixToRotate++;
			}
		}
	}
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			rotated9x9Matrix[i][j] = tempArray[i][j];
		}
	}

	rotatedTetromino.matrix = &rotated9x9Matrix[0][0];
}

void Rotate12x12matrix(unsigned char *aMatrixToRotate, int aDirection)
{
	int i;
	int j;
	unsigned char tempArray[12][12];

	if (aDirection)
	{ // COUNTERCLOCKWISE ROTATION
		for (i = 0; i < 12; i++)
		{
			for (j = 11; j >= 0; j--)
			{
				tempArray[j][i] = *aMatrixToRotate++;
			}
		}
	}

	else
	{ // CLOCKWISE ROTATION

		for (i = 11; i >= 0; i--)
		{
			for (j = 0; j < 12; j++)
			{
				tempArray[j][i] = *aMatrixToRotate++;
			}
		}
	}

	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			rotated12x12Matrix[i][j] = tempArray[i][j];
		}
	}

	rotatedTetromino.matrix = &rotated12x12Matrix[0][0];
}

void RotateMatrix(Tetromino myTetromino, int aDirection)
{
	rotatedTetromino.id = myTetromino.id;
	rotatedTetromino.width = myTetromino.width;
	rotatedTetromino.x = myTetromino.x;
	rotatedTetromino.y = myTetromino.y;

	switch (myTetromino.id)
	{
	case TET_ID_6X6:

		break;
	case TET_ID_9X9:

		Rotate9x9matrix(myTetromino.matrix, aDirection);
		break;
	case TET_ID_12X12:

		Rotate12x12matrix(myTetromino.matrix, aDirection);
		break;
	}
}

#pragma endregion

#pragma region SCORE_MECHANISM

void CheckScore()
{
	int i;
	int j;
	int tempSum;
	int tempCounter = 0;

	for (i = DISPLAY_WIDTH - 1; i >= 37; i--)
	{
		tempSum = 0;
		for (j = 1; j < DISPLAY_HEIGHT - 1; j++)
		{
			if (tetrisField[j][i])
			{
				/*Counting all the ones in a column*/
				tempSum++;
			}
		}
		/*If all the values in a column are one */
		if (tempSum == DISPLAY_HEIGHT - 2)
		{
			tempCounter++;
			int k;
			int m;
			for (k = i; k < DISPLAY_WIDTH - 1; k++)
			{
				for (m = 1; m < DISPLAY_HEIGHT - 1; m++)
				{ // all the columns in the right should shift to the left by one
					tetrisField[m][k] = tetrisField[m][k + 1];
				}
			}
			for (m = 1; m < DISPLAY_HEIGHT - 1; m++)
			{ // the last column should be set to zero
				tetrisField[m][k] = 0;
			}
		}
	}
	currentScore += (tempCounter / 3) * 100;
	if (currentScore <= 0)
	{
		level = 1;
		PORTESET = 1;
	}
	if (currentScore >= 100)
	{
		level = 2;
		PORTESET = 2;
	}
	if (currentScore >= 500)
	{
		level = 3;
		PORTESET = 4;
	}
	if (currentScore >= 1000)
	{
		level = 4;
		PORTESET = 8;
	}
	if (currentScore >= 2000)
	{
		level = 5;
		PORTESET = 16;
	}
}

#pragma endregion

#pragma region GAMEPLAY
void Play(int aButton)
{
	int temp = aButton;
	tempTetromino = currentTetromino;
	switch (temp)
	{
	case PLAY_RIGHT:
		tempTetromino.y += 3;
		if (DoesFit(tempTetromino))
		{
			currentTetromino.y += 3;
		}
		else
		{
			tempTetromino.y -= 3;
		}

		break;
	case PLAY_LEFT:
		tempTetromino.y -= 3;
		if (DoesFit(tempTetromino))
		{
			currentTetromino.y -= 3;
		}
		else
		{
			tempTetromino.y += 3;
		}

		break;
	case PLAY_ROTATE:
		if (tempTetromino.id != TET_ID_6X6)
		{

			RotateMatrix(tempTetromino, CLOCKWISE_ROTATION);
			if (DoesFit(rotatedTetromino))
			{
				currentTetromino.matrix = rotatedTetromino.matrix;
			}
			else
			{
				RotateMatrix(tempTetromino, COUNTERCLOCKWISE_ROTAION);
			}
			QuickTimer(500000);
		}
		break;
	case PLAY_EXIT:
		if (GetSwitches() == 0xb)
		{
			tempTetromino.x -= 3;
			if (DoesFit(tempTetromino))
			{
				currentTetromino.x -= 3;
			}
			else
			{
				WriteToTetrisField();
				CheckScore();
				SpawnNewTet();
				tempTetromino.x += 3;
			}
		}
		else
		{
			isGameActive = FALSE;
		}

		break;
	}
}
#pragma endregion

#pragma region USEFUL_FUNCTIONS

int Rand(void)
{
	seed = (seed * 1103515245) + 12345;
	return ((seed >> 16) & 0x7fff);
}
#pragma endregion
