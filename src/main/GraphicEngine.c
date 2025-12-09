#include "TetrisGeneral.h"

void DrawTheGame()
{
	unsigned char tempBuffer[32][128];
	int i;
	int j;
	/*Clearing the tempBuffer*/
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 128; j++)
		{
			tempBuffer[i][j] = 0;
		}
	}
	/*Printing the current tetromino accoring to its x and y coordinates on tempBuffer*/
	for (i = 0; i < currentTetromino.width; i++)
	{
		for (j = 0; j < currentTetromino.width; j++)
		{
			if (*((currentTetromino.matrix + i * currentTetromino.width) + j))
			{
				tempBuffer[currentTetromino.y + i][currentTetromino.x + j] = *((currentTetromino.matrix + i * currentTetromino.width) + j);
			}
		}
	}
	/*Mapping the two buffers and truning the corresponding pixels off or on */
	for (i = 0; i < 32; i++)
	{
		for (j = 36; j < 128; j++)
		{
			if (tetrisField[i][j] + tempBuffer[i][j])
			{
				RenderPixel(j, i, 1);
			}
			else
			{
				RenderPixel(j, i, 0);
			}
		}
	}
}

#pragma region PRINT

void PrintCharacter(char aChar, int xPosition, int yPosition, unsigned char aFont)
{
	int tempIndex = aChar - 65;
	int i;
	int j;
	if (tempIndex >= 0 && tempIndex <= 25)
	{
		switch (aFont)
		{
		case BIG_FONT:
			for (i = 0; i < 6; i++)
			{
				for (j = 0; j < 5; j++)
				{
					RenderPixel(xPosition - i, yPosition + j, alphabetA_Z[tempIndex][5 * i + j]);
				}
			}

			break;
		case LITTLE_FONT:
			for (i = 0; i < 5; i++)
			{
				for (j = 0; j < 3; j++)
				{
					RenderPixel(xPosition + j, yPosition + i, alphabet[tempIndex][3 * i + j]);
				}
			}

			break;
		}
	}
	if (aChar == 26)
	{
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 3; j++)
			{
				RenderPixel(xPosition + j, yPosition + i, alphabet[26][3 * i + j]);
			}
		}
	}
	if (aChar == 32)
	{
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 3; j++)
			{
				RenderPixel(xPosition + j, yPosition + i, alphabet[27][3 * i + j]);
			}
		}
	}
}

void PrintDigit(char aDigit, int xPosition, int yPosition, unsigned char aFont)
{
	int tempIndex = aDigit - 48;
	int i;
	int j;
	switch (aFont)
	{
	case BIG_FONT:
		for (i = 0; i < 6; i++)
		{
			for (j = 0; j < 5; j++)
			{
				RenderPixel(xPosition - i, yPosition + j, digits0_9[tempIndex][5 * i + j]);
			}
		}
		break;

	case LITTLE_FONT:
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 3; j++)
			{
				RenderPixel(xPosition + j, yPosition + i, digits[tempIndex][3 * i + j]);
			}
		}
		break;
	}
}

void PrintString(char *aString, int xPosition, int yPosition, unsigned char aFont)
{
	int tempX = xPosition;
	int tempY = yPosition;
	int i;
	int j;
	switch (aFont)
	{
	case BIG_FONT:

		while (*aString != 0)
		{
			PrintCharacter(*aString, tempX, tempY, aFont);
			if (*aString == 32)
			{
				for (i = 0; i < 6; i++)
				{
					for (j = 0; j < 5; j++)
					{
						RenderPixel(xPosition - i, yPosition + j, alphabetA_Z[27][5 * i + j]);
					}
				}
			}
			aString++;
			tempY += 6;
		}
		break;

	case LITTLE_FONT:
		while (*aString != 0)
		{

			PrintCharacter(*aString, tempX, tempY, aFont);
			if (*aString == 32)
			{
				for (i = 0; i < 5; i++)
				{
					for (j = 0; j < 3; j++)
					{
						RenderPixel(tempX + j, tempY + i, alphabet[27][3 * i + j]);
					}
				}
			}
			aString++;
			tempX += 4;
		}
		break;
	}
}

void PrintNumber(int aNumber, int xPosition, int yPosition, unsigned char aFont)
{

	int tempY = yPosition;
	int tempX = xPosition;
	int i;

	int tempCounter = 1;
	int tempNum1 = aNumber;
	int tempNum2 = aNumber;
	/*Counting the digits*/
	while (tempNum1 /= 10)
	{
		tempCounter++;
	}

	char tempDigitArray[tempCounter];
	/*Extracting one digits from the right and save it in a temp array*/
	for (i = 0; i < tempCounter; i++)
	{
		tempDigitArray[i] = (tempNum2 % 10) + 48;
		tempNum2 /= 10;
	}

	switch (aFont)
	{
	case BIG_FONT:
		/*Looping backward to get the right digits*/
		for (i = tempCounter - 1; i >= 0; i--)
		{
			PrintDigit(tempDigitArray[i], tempX, tempY, aFont);
			tempY += 6;
		}
		break;

	case LITTLE_FONT:
		for (i = tempCounter - 1; i >= 0; i--)
		{
			PrintDigit(tempDigitArray[i], tempX, tempY, aFont);
			tempX += 4;
		}
		break;
	}
}

void PrintTetromino(Tetromino myTetromino, int xPosition, int yPosition)
{
	int i;
	int j;
	int tempY = yPosition;
	int tempX = xPosition;
	unsigned char *tempP = myTetromino.matrix;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			RenderPixel(tempX + j, tempY + i, 0);
		}
	}
	for (i = 0; i < myTetromino.width; i++)
	{
		for (j = 0; j < myTetromino.width; j++)
		{
			RenderPixel(tempX + j, tempY + i, *tempP);
			tempP++;
		}
	}
}

#pragma endregion

#pragma region PIXEL

void RenderPixel(int xPosition, int yPosition, unsigned char aState)
{
	if (xPosition < 128 && yPosition < 32 && aState <= 1)
	{
		/*Getting the right position in oled display buffer*/
		short bufferPos = ((yPosition / 8) * 128) + xPosition;

		if (aState == 1)
		{
			OLED_DisplayBuffer[bufferPos] = (OLED_DisplayBuffer[bufferPos] | (0x1 << (yPosition % 8)));
		}
		else if (aState == 0)
		{
			OLED_DisplayBuffer[bufferPos] = (OLED_DisplayBuffer[bufferPos] & ~(0x1 << (yPosition % 8)));
		}
	}
}

void ClearDisplay()
{
	int i;
	for (i = 0; i < 512; i++)
	{
		OLED_DisplayBuffer[i] = 0;
	}
}

#pragma endregion