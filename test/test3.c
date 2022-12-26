#include <stdio.h>

typedef struct _
{
    int horiCheck;
    int verCheck;
} coord;

int spaces[10][4][2];
int lenSpace[10] = {0};
int spaceCount = 0;
coord cordCheck[4][4];

int checkCell(int x, int y, char arr[4][4])
{
    if (arr[x][y] == '*')
        return 1;
    return 0;
}

int isInArr(int n, int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == n)
            return 1;
    }

    return 0;
}

void updateHorizon(int x, int y, char arr[4][4], int lens[], int wordLens[], int words)
{
    int tempX = x;
    int i = 0;
    while (tempX < 4)
    {
        if (checkCell(tempX, y, arr))
        {
            spaces[spaceCount][i][0] = tempX;
            spaces[spaceCount][i][1] = y;
            cordCheck[tempX][y].horiCheck = 1;
            i++;
        }
        tempX++;
    }
    while (x >= 0)
    {
        x--;
        if (checkCell(x, y, arr))
        {
            spaces[spaceCount][i][0] = x;
            spaces[spaceCount][i][1] = y;
            cordCheck[x][y].horiCheck = 1;
            i++;
        }
    }

    if (isInArr(i, wordLens, words))
    {
        lenSpace[spaceCount] = i;
        spaceCount++;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            spaces[spaceCount][i][0] = -1;
            spaces[spaceCount][i][1] = -1;
        }
    }
}

void updateVertical(int x, int y, char arr[4][4], int lens[], int wordLens[], int words)
{
    int tempY = y;
    int i = 0;
    while (tempY < 4)
    {
        if (checkCell(x, tempY, arr))
        {
            spaces[spaceCount][i][0] = x;
            spaces[spaceCount][i][1] = tempY;
            cordCheck[x][tempY].horiCheck = 1;
            i++;
        }
        tempY++;
    }
    while (y >= 0)
    {
        y--;
        if (checkCell(x, y, arr))
        {
            spaces[spaceCount][i][0] = x;
            spaces[spaceCount][i][1] = y;
            cordCheck[x][y].horiCheck = 1;
            i++;
        }
    }

    if (isInArr(i, wordLens, words))
    {
        lenSpace[spaceCount] = i;
        spaceCount++;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            spaces[spaceCount][i][0] = -1;
            spaces[spaceCount][i][1] = -1;
        }
    }
}

int main()
{

    char arr[4][4] = {{'#', '#', '#', '#'},
                      {'#', '#', '*', '#'},
                      {'*', '*', '*', '*'},
                      {'#', '#', '*', '#'}};

    int wordLengths[] = {4, 2, 3};
    int words = 3;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            spaces[i][j][0] = -1;
            spaces[i][j][1] = -1;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cordCheck[i][j].horiCheck = 0;
            cordCheck[i][j].verCheck = 0;
        }
    }

    updateHorizon(1, 2, arr, wordLengths, wordLengths, words);
    updateHorizon(2, 1, arr, wordLengths, wordLengths, words);
    updateVertical(2, 0, arr, wordLengths, wordLengths, words);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("(%d %d)  ", spaces[i][j][0], spaces[i][j][1]);
        }
        printf(" - %d \n", lenSpace[i]);
    }

    return 0;
}