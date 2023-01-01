#include <stdio.h>
#include <string.h>

#define gridRowFix 20
#define gridColFix 20
#define wordsNum 20
#define wordLen 10
#define maxSpacelen 20
#define max ((gridRowFix > gridColFix) ? gridRowFix : gridColFix)
int gridRow = 20;
int gridCol = 20;

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
int spaceLens[maxSpacelen] = {0};
int spaceOccur[maxSpacelen] = {0};
int spaceCount = 0;
cellCheck cordCheck[gridRowFix][gridColFix];

char grid[gridRowFix][gridColFix];
char words[wordsNum][wordLen];
int wordLens[wordsNum];
int wordLensOccur[wordsNum];
int wordCount = 0;

int checkCell(int x, int y, char arr[gridRowFix][gridColFix])
{
    if (arr[x][y] != '*')
        return 1;
    return 0;
}

int isInValid(char x)
{
    if ((x == '#') || (x == '*') || ((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z')))
        return 0;
    else
        return 1;
}

int isAplha(char x)
{
    if (((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z')))
        return 1;
    else
        return 0;
}

int checkInvalidInput()
{
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            if (isInValid(grid[i][j]))
                return 1;
        }
    }

    for (int i = 0; i < wordCount; i++)
    {
        for (int j = 0; j < wordLens[i]; j++)
        {
            if (!isAplha(words[i][j]))
                return 1;
        }
    }

    return 0;
}

void updateVertical(int x, int y, char arr[gridRowFix][gridColFix])
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
        spaceLens[spaceCount] = i;
        spaceCount++;
    }
    else
    {
        spacesCords[spaceCount][0].x = -1;
        spacesCords[spaceCount][0].y = -1;
    }
}

void updateHorizon(int x, int y, char arr[gridRowFix][gridColFix])
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
        spaceLens[spaceCount] = i;
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
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            cordCheck[i][j].horiCheck = 1;
            cordCheck[i][j].verCheck = 1;
        }
    }
}

void updateSpaceVar()
{
    initializeSpaceVar();

    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            if (checkCell(i, j, grid))
            {

                if (cordCheck[i][j].horiCheck)
                {
                    updateHorizon(i, j, grid);
                }

                if (cordCheck[i][j].verCheck)
                {
                    updateVertical(i, j, grid);
                }
            }
        }
    }
}

void getInputs()
{
    gridRow = 0;
    while (1)
    {
        grid[gridRow][0] = '\0';
        fgets(&grid[gridRow][0], gridCol, stdin);

        if (strlen(&grid[gridRow][0]) == 1)
            break;

        gridRow++;
    }

    gridCol = strlen(&grid[0][0]) - 1;

    while (wordCount < wordsNum)
    {
        words[wordCount][0] = '\0';
        fgets(&words[wordCount][0], wordLen, stdin);

        if (strlen(&words[wordCount][0]) == 1)
            break;

        wordLens[wordCount] = strlen(&words[wordCount][0]) - 1;
        (wordCount)++;
    }
}

int isSubset()
{
    if (spaceCount < wordCount)
        return 0;

    int arrTemp[spaceCount];
    for (int i = 0; i < spaceCount; i++)
    {
        arrTemp[i] = spaceLens[i];
    }

    int flag;
    for (int i = 0; i < wordCount; i++)
    {
        flag = 1;
        for (int j = 0; j < spaceCount; j++)
        {
            if (wordLens[i] == arrTemp[j])
            {
                flag = 0;
                arrTemp[j] = -1;
                break;
            }
        }

        if (flag)
            return 0;
    }

    return 1;
}

void printGrid()
{
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

void updateOccur()
{

    int tempArr[wordCount];
    int count;

    for (int i = 0; i < wordCount; i++)
    {
        tempArr[i] = wordLens[i];
    }

    for (int i = 0; i < wordCount; i++)
    {
        count = 0;
        if (tempArr[i] == -1)
            continue;

        for (int j = 0; j < wordCount; j++)
        {
            if (wordLens[i] == tempArr[j])
            {
                count++;
                tempArr[j] = -1;
            }
        }

        for (int j = 0; j < wordCount; j++)
        {
            if (wordLens[j] == wordLens[i])
            {
                wordLensOccur[j] = count;
            }
        }
    }
}

void swapInt(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swapWords(char arr1[], char arr2[])
{
    char temp[wordLen];
    strcpy(temp, arr1);
    strcpy(arr1, arr2);
    strcpy(arr2, temp);
}

void sortWordOccur()
{
    updateOccur();
    for (int i = 0; i < wordCount - 1; i++)
    {
        for (int j = 0; j < wordCount - i - 1; j++)
        {
            if (wordLensOccur[j] > wordLensOccur[j + 1])
            {
                swapInt(&wordLensOccur[j], &wordLensOccur[j + 1]);
                swapInt(&wordLens[j], &wordLens[j + 1]);
                swapWords(&words[j][0], &words[j + 1][0]);
            }
        }
    }
}

int word2space(int n, char word[wordLen], spaceCoordinate cord[max])
{
    char tempGrid[gridRowFix][gridColFix];
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            tempGrid[i][j] = grid[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (grid[cord[i].x][cord[i].y] == '#' || grid[cord[i].x][cord[i].y] == word[i])
        {
            grid[cord[i].x][cord[i].y] = word[i];
        }
        else
        {
            for (int i = 0; i < gridRow; i++)
            {
                for (int j = 0; j < gridCol; j++)
                {
                    grid[i][j] = tempGrid[i][j];
                }
            }
            return 1;
        }
    }

    return 0;
}

int checkGridFill()
{
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            if (grid[i][j] == '#')
            {
                return 0;
            }
        }
    }
    return 1;
}

int Fill(int arrSpaceLens[], int arrWordLens[])
{
    if (checkGridFill())
        return 0;

    int tempSpaceLens[spaceCount];
    int tempWordLens[wordCount];
    char tempGrid[gridRowFix][gridColFix];
    int temp;
    int temp1;

    for (int i = 0; i < spaceCount; i++)
    {
        tempSpaceLens[i] = arrSpaceLens[i];
    }
    for (int i = 0; i < wordCount; i++)
    {
        tempWordLens[i] = arrWordLens[i];
    }
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            tempGrid[i][j] = grid[i][j];
        }
    }

    int flag = 1;
    for (int j = 0; j < wordCount; j++)
    {
        flag = 1;
        if (tempWordLens[j] == -1)
            continue;

        for (int i = 0; i < spaceCount; i++)
        {
            if (tempSpaceLens[i] == -1)
                continue;

            if (tempSpaceLens[i] == tempWordLens[j] && (word2space(tempSpaceLens[i], &words[j][0], &spacesCords[i][0]) == 0))
            {
                flag = 0;
                temp = tempSpaceLens[i];
                temp1 = tempWordLens[j];
                tempSpaceLens[i] = -1;
                tempWordLens[j] = -1;

                if (Fill(tempSpaceLens, tempWordLens))
                {
                    tempSpaceLens[i] = temp;
                    tempWordLens[j] = temp1;
                    for (int i = 0; i < gridRow; i++)
                    {
                        for (int j = 0; j < gridCol; j++)
                        {
                            grid[i][j] = tempGrid[i][j];
                        }
                    }
                }
            }
        }
        if (flag)
        {
            return 1;
        }
    }

    return 0;
}

int main()
{

    getInputs();

    if (checkInvalidInput())
    {
        printf("INVALID INPUT\n");
        return 0;
    }

    updateSpaceVar();

    if (isSubset() == 0)
    {
        printf("IMPOSSIBLE\n");
        return 0;
    }

    sortWordOccur();
    Fill(spaceLens, wordLens);

    if (checkGridFill())
        printGrid();
    else
        printf("IMPOSSIBLE\n");

    return 0;
}