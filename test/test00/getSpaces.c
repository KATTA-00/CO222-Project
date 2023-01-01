#include <stdio.h>

// predefined size
#define maxSpacelen 10
#define rows 4
#define cols 4
#define max ((rows > cols) ? rows : cols)

// structs for check the cells and spaceCoordinates
typedef struct _
{
    int horiCheck;
    int verCheck;
} cellCheck;

typedef struct __
{
    int x;
    int y;
} spaceCoordinate;

// global variables
spaceCoordinate spacesCords[maxSpacelen][max];
int spaceLen[maxSpacelen] = {0};
int spaceCount = 0;
cellCheck cordCheck[rows][cols];

int checkCell(int x, int y, char arr[rows][cols])
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

void updateVertical(int x, int y, char arr[rows][cols], int wordLens[], int words)
{
    int tempX = x;
    int i = 0;
    while (tempX < rows)
    {
        if (checkCell(tempX, y, arr))
        {
            spacesCords[spaceCount][i].x = tempX;
            spacesCords[spaceCount][i].y = y;
            cordCheck[tempX][y].verCheck = 0;
            i++;
        }
        else
            break;
        tempX++;
    }

    if (isInArr(i, wordLens, words))
    {
        spaceLen[spaceCount] = i;
        spaceCount++;
    }
    else
    {
        for (int i = 0; i < max; i++)
        {
            spacesCords[spaceCount][i].x = -1;
            spacesCords[spaceCount][i].y = -1;
        }
    }
}

void updateHorizon(int x, int y, char arr[rows][cols], int wordLens[], int words)
{
    int tempY = y;
    int i = 0;
    while (tempY < cols)
    {
        if (checkCell(x, tempY, arr))
        {
            spacesCords[spaceCount][i].x = x;
            spacesCords[spaceCount][i].y = tempY;
            cordCheck[x][tempY].horiCheck = 0;
            i++;
        }
        else
            break;
        tempY++;
    }

    if (isInArr(i, wordLens, words))
    {
        spaceLen[spaceCount] = i;
        spaceCount++;
    }
    else
    {
        for (int i = 0; i < max; i++)
        {
            spacesCords[spaceCount][i].x = -1;
            spacesCords[spaceCount][i].y = -1;
        }
    }
}

void initializeSpaceVar()
{
    for (int i = 0; i < maxSpacelen; i++)
    {
        for (int j = 0; j < max; j++)
        {
            spacesCords[i][j].x = -1;
            spacesCords[i][j].y = -1;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cordCheck[i][j].horiCheck = 1;
            cordCheck[i][j].verCheck = 1;
        }
    }
}

void updateSpaceVar(char arr[rows][cols], int wordLenArr[], int wordCount)
{
    initializeSpaceVar();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (checkCell(i, j, arr))
            {

                if (cordCheck[i][j].horiCheck)
                {
                    updateHorizon(i, j, arr, wordLenArr, wordCount);
                }

                if (cordCheck[i][j].verCheck)
                {
                    updateVertical(i, j, arr, wordLenArr, wordCount);
                }
            }
        }
    }
}

int main()
{

    char arr[rows][cols] = {{'#', '#', '*', '*'},
                            {'#', '*', '*', '#'},
                            {'*', '*', '*', '*'},
                            {'#', '*', '*', '#'}};

    int wordLengths[] = {4, 3};
    int words = 2;

    updateSpaceVar(arr, wordLengths, words);

    printf("%d\n", spaceCount);

    for (int i = 0; i < maxSpacelen; i++)
    {
        for (int j = 0; j < max; j++)
        {
            printf("(%d %d)  ", spacesCords[i][j].x, spacesCords[i][j].y);
        }
        printf(" - %d \n", spaceLen[i]);
    }

    return 0;
}