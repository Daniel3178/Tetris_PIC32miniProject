#include "TetrisGeneral.h"
#include "pic32max.h"

Player topPlayer[4] = {
    {"", 0, "FIRST"},
    {"", 0, "SECOND"},
    {"", 0, "THIRD"},
    {"", 0, "CURRENT"},
};

#pragma region ENDGAME_STUFF
/*Takes the two initials from the user*/
void RegisterPlayer()
{

    ClearDisplay();
    PrintString("NAME", 60, 4, BIG_FONT);
    char firstLetter = '@';
    char secondLetter = '@';
    char thirdLetter = '@';
    while (!(GetButtons() & 0x8))
    {
        if ((GetButtons() & 0x4) && firstLetter <= 'Z')
        {
            PrintCharacter(++firstLetter, 50, 7, BIG_FONT);
        }
        if ((GetButtons() & 0x2) && firstLetter > 'A')
        {
            PrintCharacter(--firstLetter, 50, 7, BIG_FONT);
        }
    }
    delay(2);
    while (!(GetButtons() & 0x8))
    {

        if ((GetButtons() & 0x4) && secondLetter <= 'Z')
        {
            PrintCharacter(++secondLetter, 50, 13, BIG_FONT);
        }
        if ((GetButtons() & 0x2) && secondLetter > 'A')
        {
            PrintCharacter(--secondLetter, 50, 13, BIG_FONT);
        }
    }
    delay(2);
        while (!(GetButtons() & 0x8))
    {

        if ((GetButtons() & 0x4) && thirdLetter <= 'Z')
        {
            PrintCharacter(++thirdLetter, 50, 19, BIG_FONT);
        }
        if ((GetButtons() & 0x2) && thirdLetter > 'A')
        {
            PrintCharacter(--thirdLetter, 50, 19, BIG_FONT);
        }
    }
    delay(2);

    topPlayer[3].name[0] = firstLetter;
    topPlayer[3].name[1] = secondLetter;
    topPlayer[3].name[2] = thirdLetter;
    topPlayer[3].name[3] =0;
    topPlayer[3].score = currentScore;
    currentScore = 0;
}
/*Selection sort for sorting the top player array*/
void UpdateLeaderBoard()
{
    int i;
    int j;
    int m;
    for (i = 0; i < 3; i++)
    {
        m = i;
        for (j = i + 1; j < 4; j++)
        {

            if (topPlayer[j].score >= topPlayer[i].score)
            {
                m = j;
            }
        }
        if (m != i)
        {

            Player temp;
            temp.name[0] = topPlayer[i].name[0];
            temp.name[1] = topPlayer[i].name[1];
            temp.name[2] = topPlayer[i].name[2];
            temp.name[3] = 0;
            temp.score = topPlayer[i].score;

            topPlayer[i].name[0] = topPlayer[m].name[0];
            topPlayer[i].name[1] = topPlayer[m].name[1];
            topPlayer[i].name[2] = topPlayer[m].name[2];
            topPlayer[i].name[3] = 0;
            topPlayer[i].score = topPlayer[m].score;

            topPlayer[m].name[0] = temp.name[0];
            topPlayer[m].name[1] = temp.name[1];
            topPlayer[m].name[2] = temp.name[2];
            topPlayer[m].name[3] = 0;
            topPlayer[m].score = temp.score;
        }
    }
}

void DisplayCurrentPlayer()
{
    ClearDisplay();
    PrintString("ID", 90, 4, BIG_FONT);
    PrintString(&topPlayer[3].name[0], 80, 4, BIG_FONT);
    PrintString("SCORE", 60, 4, BIG_FONT);
    PrintNumber(topPlayer[3].score, 50, 4, BIG_FONT);
    QuickTimer(20000000);
}

void EndGameRoutine()
{
    ClearDisplay();
    delay(1000);
    PrintString("GAME", 90, 5, BIG_FONT);
    PrintString("OVER", 80, 5, BIG_FONT);
    delay(10000);
    ClearDisplay();
    RegisterPlayer();
    DisplayCurrentPlayer();
    UpdateLeaderBoard();
    delay(5000);
    ClearDisplay();
    level =1;
    PORTECLR = 0xff;
}
#pragma endregion

#pragma region LEADERBOARD
void InitializeLeaderBoardField()
{
    unsigned char i = 0;
    unsigned char j = 0;
    ClearDisplay();

    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 128; j++)
        {
            if (i == 0 || i == 31 || i == 9 || j == 42 || j == 0 || j == 127)
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

void DisplayLeaderBoard()
{
    InitializeLeaderBoardField();
    PrintString("PLAYER ID", 3, 2, LITTLE_FONT);
    PrintString("RANK", 64, 2, LITTLE_FONT);
    PrintString("SCORE", 99, 2, LITTLE_FONT);

    if (topPlayer[0].name[0] != 0 && topPlayer[0].score > 0)
    {
        PrintString(&topPlayer[0].name[0], 15, 11, LITTLE_FONT);
        PrintString(&topPlayer[0].positionBuffer[0], 64, 11, LITTLE_FONT);
        PrintNumber(topPlayer[0].score, 99, 11, LITTLE_FONT);
    }
    if (topPlayer[1].name[0] != 0 && topPlayer[1].score > 0)
    {
        PrintString(&topPlayer[1].name[0], 15, 18, LITTLE_FONT);
        PrintString(&topPlayer[1].positionBuffer[0], 64, 18, LITTLE_FONT);
        PrintNumber(topPlayer[1].score, 99, 18, LITTLE_FONT);
    }
    if (topPlayer[2].name[0] != 0 && topPlayer[2].score > 0)
    {
        PrintString(&topPlayer[2].name[0], 15, 25, LITTLE_FONT);
        PrintString(&topPlayer[2].positionBuffer[0], 64, 25, LITTLE_FONT);
        PrintNumber(topPlayer[2].score, 99, 25, LITTLE_FONT);
    }
}
#pragma endregion
