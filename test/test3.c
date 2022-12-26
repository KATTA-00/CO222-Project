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

void updateHorizon(int x, int y, char arr[4][4], int lens[])
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

    lenSpace[spaceCount] = i;
    spaceCount++;
}

int main()
{

    char arr[4][4] = {{'#', '#', '#', '#'},
                      {'#', '#', '*', '#'},
                      {'#', '*', '*', '*'},
                      {'#', '#', '*', '#'}};

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

    updateHorizon(3, 2, arr, 1);
    updateHorizon(2, 1, arr, 2);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("(%d %d)/%d  ", spaces[i][j][0], spaces[i][j][1]);
        }
        printf(" - %d \n", lenSpace[i]);
    }

    return 0;
}