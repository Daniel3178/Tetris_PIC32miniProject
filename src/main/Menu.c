#include "TetrisGeneral.h"

#pragma region RUN_GAME/LEADERBOARD

void RunTheGame()
{

    ClearDisplay();
    InitializeTetrisField();
    SpawnNewTet();
    PrintString("SCORE", 34, 2, BIG_FONT);
    isGameActive = TRUE;
    while (isGameActive)
    {
        DrawTheGame();
        Play(GetButtons());
        PrintTetromino(nextTetromino, 5, 9);
        PrintNumber(currentScore, 25, 5, BIG_FONT);
    }
    EndGameRoutine();
}

void RunTheLeaderBoard()
{
    DisplayLeaderBoard();
    while (!(GetButtons() & 0x1))
    {
    }
    ClearDisplay();
}

#pragma endregion

#pragma region USEFUL_FUNCTIONS

unsigned char GetUserOption()
{
    int tempX = 40;
    int tempY = 13;
    PrintString("TETRIS MENU", 44, 4, LITTLE_FONT);
    PrintString("PLAY", 48, 13, LITTLE_FONT);
    PrintString("HIGHEST SCORE", 48, 21, LITTLE_FONT);
    while (!(GetButtons() & 0x8))
    {
        switch (GetButtons())
        {
        case 2:
            tempX = 40;
            tempY = 13;
            break;

        case 4:
            tempX = 40;
            tempY = 21;
            break;
        }
        PrintCharacter(32, 40, 13, LITTLE_FONT);
        PrintCharacter(32, 40, 21, LITTLE_FONT);
        PrintCharacter(26, tempX, tempY, LITTLE_FONT);
    }
    /*According to the last x and y coordinate of the select box return the option*/
    if (tempY == 13)
    {
        return 1;
    }
    if (tempY == 21)
    {
        return 2;
    }
}

void DisplayDevelopersName(){
    ClearDisplay();
    PrintString("DEVELOPED BY", 44, 7, LITTLE_FONT);
    PrintString("NAVEED AND DANIEL", 35, 17, LITTLE_FONT);
    QuickTimer(10000000);
    ClearDisplay(); 
}

#pragma endregion

void RunTetris()
{
    InitializeUNO32();
    DisplayDevelopersName();
    while (1)
    {
        switch (GetUserOption())
        {
        case 1:
            RunTheGame();
            break;
        case 2:
            RunTheLeaderBoard();
            break;
        }
    }
}
