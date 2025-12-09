#ifndef _Tetris_Config_H
#define _Tetris_Config_H

/*Definitions*/
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32
#define FONT_WIDTH 5
#define FONT_HEIGHT 6
#define TET_ID_6X6 1
#define TET_ID_9X9 2
#define TRUE 1
#define FALSE 0
#define BIG_FONT 0
#define LITTLE_FONT 1
#define TET_ID_12X12 3
#define PLAY_EXIT 0x1
#define PLAY_RIGHT 0x2
#define PLAY_LEFT 0x4
#define PLAY_ROTATE 0x8
#define TETRIS_FIELD_WIDTH 30
#define TETRIS_FIELD_HEIGHT 127
#define CLOCKWISE_ROTATION 0
#define COUNTERCLOCKWISE_ROTAION 1

typedef struct Tetromino
{
	unsigned char *matrix;
	int width;
	int x;
	int y;
	unsigned char id;
	
} Tetromino;

typedef struct Player
{
	char name[4];
	int score;
	char positionBuffer[8];

} Player;

/*Tetrominoes & font declaration */
unsigned char digits[10][15];
unsigned char alphabet[28][15];
unsigned char digits0_9[10][30];
unsigned char alphabetA_Z[28][30];
unsigned char tetrisField[32][128];
unsigned char OLED_DisplayBuffer[512];

Tetromino tetCollection[7];
Tetromino rotatedTetromino;
Tetromino currentTetromino;
Tetromino tempTetromino;
Tetromino nextTetromino;


int seed; /*For randomizing a number*/
int timeoutCount; /*For speed of the game */
int currentScore; /*For saving the current score*/
unsigned char level; /*For keeping track of the current level in the game*/
unsigned char isGameActive; /*For running or ending the game*/

/* Functions */
int GetSwitches();
int GetButtons(void); /*Returns the state of 4 btns in form of 4 bits where bit 0 = btn1*/
int Rand(void); /*Returns a random number*/
void user_isr(); /*This function is a part of interupt service routine and is used for updating disply and some game mechanism*/
void InitializeTetrisField(); /*This will set up the border of the game field */
void enable_interrupts(); /*enables interrupt*/
void SpawnNewTet(); /*This func will generate a new tetromino and adjusts its x and y coordinate in the game*/
void ClearDisplay(); /*This will turn off all the pixels in the display*/
void InitializeUNO32(); /*This will initialize all the necessary parts in the hardware such as display, btns, swiches, timer, enterupt etc*/
void DrawTheGame(); /*This will loop through the game matrix and turn the corresponding pixels on the display off or on accordingly*/
void DisplayCurrentPlayer(); /*This will display the current player's name and score after registeration*/
void InitializeLeaderBoardField(); /*This will set the borders on the leaderboard */
void DisplayLeaderBoard(); /*This will display the data on the leaderboard*/
void EndGameRoutine(); /*This will display an ending message and will call a player registration routin*/
void RunTetris(); /*This will trigger the program and is used for simplifying the main function*/
void Play(int aButton); /*This will take a btn and will update the game accordingly t.ex, move or rotate the current tetromino*/
void QuickTimer(int timeout); /*A simple timer */
void RenderPixel(int xPos, int yPos, unsigned char state); /*It takes an x and y coordinate and according to third argument, it will
either turn the corresponding pixel on or off*/
void RotateMatrix(Tetromino inputTet, int rotationDirection); /*It takes a tetromino and rotates it either clockwise or counter clockwise*/
void PrintNumber(int aNumber, int xPosition, int yPosition, unsigned char aFont); /*It print a number in a specific place on the disply*/
void PrintCharacter(char aChar, int xPosition, int yPosition, unsigned char aFont); /*It prints a character in a specific place on the display*/
void PrintString(char *aString, int xPosition, int yPosition, unsigned char aFont); /*It uses printCharacter to print a string in a specific place on the display*/
void PrintTetromino(Tetromino myTetromino, int xPosition, int yPosition); /*This will print a tetromino in a specific place on the display*/

#endif