#include <stdio.h>
#include <string.h>

#define gridRow 4
#define gridCol 4
#define wordsNum 16
#define wordLen 10
#define maxSpacelen 10
#define max ((gridRow > gridCol) ? gridRow : gridCol)

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

spaceCoordinate spacesCords[maxSpacelen][max];
int spaceLen[maxSpacelen] = {0};
int spaceCount = 0;
cellCheck cordCheck[gridRow][gridCol];

int checkCell(int x, int y, char arr[gridRow][gridCol])
{
    if (arr[x][y] == '#')
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

void updateVertical(int x, int y, char arr[gridRow][gridCol])
{
    int tempX = x;
    int i = 0;
    while (tempX < gridRow)
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

    if (i != 1)
    {
        spaceLen[spaceCount] = i;
        spaceCount++;
    }
    else
    {
        spacesCords[spaceCount][0].x = -1;
        spacesCords[spaceCount][0].y = -1;
    }
}

void updateHorizon(int x, int y, char arr[gridRow][gridCol])
{
    int tempY = y;
    int i = 0;
    while (tempY < gridCol)
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

    if (i != 1)
    {
        spaceLen[spaceCount] = i;
        spaceCount++;
    }
    else
    {
        spacesCords[spaceCount][0].x = -1;
        spacesCords[spaceCount][0].y = -1;
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

    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            cordCheck[i][j].horiCheck = 1;
            cordCheck[i][j].verCheck = 1;
        }
    }
}

void updateSpaceVar(char arr[gridRow][gridCol])
{
    initializeSpaceVar();

    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            if (checkCell(i, j, arr))
            {

                if (cordCheck[i][j].horiCheck)
                {
                    updateHorizon(i, j, arr);
                }

                if (cordCheck[i][j].verCheck)
                {
                    updateVertical(i, j, arr);
                }
            }
        }
    }
}

int main()
{

    char grid[gridRow][gridCol];
    char temp;
    char words[wordsNum][wordLen];
    int wordLens[wordsNum];
    int wordCount = 0;

    for (int i = 0; i < gridRow; i++)
    {
        scanf("%[^\n]%*c\n", &grid[i][0]);
    }

    while (wordCount < wordsNum)
    {
        words[wordCount][0] = '\0';
        fgets(&words[wordCount][0], wordLen, stdin);

        if (strlen(&words[wordCount][0]) == 1)
            break;

        wordLens[wordCount] = strlen(&words[wordCount][0]) - 1;
        wordCount++;
    }

    updateSpaceVar(grid);

    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < wordCount; i++)
    {
        printf("%d ", wordLens[i]);
    }

    printf("\n");

    for (int i = 0; i < spaceCount; i++)
    {
        printf("%d ", spaceLen[i]);
    }

    return 0;
}