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
int spaceLens[maxSpacelen] = {0};
int spaceCount = 0;
cellCheck cordCheck[gridRow][gridCol];

char grid[gridRow][gridCol];
char words[wordsNum][wordLen];
int wordLens[wordsNum];
int wordCount = 0;

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
        spaceLens[spaceCount] = i;
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

void swapInt(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swapSpaceCords(spaceCoordinate arr1[max], spaceCoordinate arr2[max])
{
    spaceCoordinate temp[max];

    for (int i = 0; i < max; i++)
    {
        temp[i].x = arr1[i].x;
        temp[i].y = arr1[i].y;
    }
    for (int i = 0; i < max; i++)
    {
        arr1[i].x = arr2[i].x;
        arr1[i].y = arr2[i].y;
    }
    for (int i = 0; i < max; i++)
    {
        arr2[i].x = temp[i].x;
        arr2[i].y = temp[i].y;
    }
}

void swapWords(char arr1[], char arr2[])
{
    char temp[wordLen];
    strcpy(temp, arr1);
    strcpy(arr1, arr2);
    strcpy(arr2, temp);
}

void sortWords()
{

    for (int i = 0; i < wordCount - 1; i++)
    {

        for (int j = 0; j < wordCount - i - 1; j++)
        {
            if (wordLens[j] < wordLens[j + 1])
            {
                swapInt(&wordLens[j], &wordLens[j + 1]);
                swapWords(&words[j][0], &words[j + 1][0]);
            }
        }
    }
}

void sortSpaceCord()
{

    for (int i = 0; i < spaceCount - 1; i++)
    {

        for (int j = 0; j < spaceCount - i - 1; j++)
        {
            if (spaceLens[j] < spaceLens[j + 1])
            {
                swapInt(&spaceLens[j], &spaceLens[j + 1]);
                swapSpaceCords(&spacesCords[j][0], &spacesCords[j + 1][0]);
            }
        }
    }
}

int word2space(int n, char word[wordLen], spaceCoordinate cord[max])
{
    for (int i = 0; i < n; i++)
    {
        if (grid[cord[i].x][cord[i].y] == '#' || grid[cord[i].x][cord[i].y] == word[i])
        {
            grid[cord[i].x][cord[i].y] = word[i];
        }
        else
        {
            for (int j = 0; j < i; j++)
            {
                grid[cord[i].x][cord[i].y] = '#';
            }
            return 1;
        }
    }
    return 0;
}

void gridFill(int wordStart, int spaceStart)
{
}

int main()
{

    getInputs();
    updateSpaceVar();
    sortSpaceCord();
    sortWords();

    if (isSubset() == 0)
        printf("IMPOSSIBLE\n");

    printGrid();

    //////////////////////////////////////////////////////////////////////////////

    printf("%d\n", wordCount);
    for (int i = 0; i < wordCount; i++)
    {
        printf("%d ", wordLens[i]);
    }
    printf("\n%d\n", spaceCount);

    for (int i = 0; i < spaceCount; i++)
    {
        printf("%d ", spaceLens[i]);
    }

    //printf("\n%d", isSubset());

    // printf("\n");
    // for (int i = 0; i < spaceCount; i++)
    // {
    //     for (int j = 0; j < max; j++)
    //     {
    //         printf("(%d,%d) ", spacesCords[i][j].x, spacesCords[i][j].y);
    //     }
    //     printf("%d\n", spaceLens[i]);
    // }
    ////////////////////////////////////////////////////////////////////////////////
    return 0;
}