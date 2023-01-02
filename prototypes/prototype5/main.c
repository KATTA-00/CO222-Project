// import the libary
#include <stdio.h>
#include <string.h>

// define the macros
#define gridRowFix 20
#define gridColFix 20
#define wordsNum 20
#define wordLen 10
#define maxSpacelen 20
#define max ((gridRowFix > gridColFix) ? gridRowFix : gridColFix)

// define a struct to store is cell is checked
typedef struct _
{
    int horiCheck;
    int verCheck;
} cellCheck;

// define a struct to hold x,y coordinate
typedef struct __
{
    int x;
    int y;
} coordinate;

// initalize row and col
int gridRow = 20;
int gridCol = 20;

/*
    define the global variables
        grid - store the grid
        words - store the words
        wordLens - store the length of the words
        wordLensOccur - store the occurances of each word
        wordCount - word count
        spacesCords - store the spaces coordinates together
        spaceLens - legths arr of spaces
        spaceCount - count of spaces
        cordCheck - store is the cell is checked

*/
char grid[gridRowFix][gridColFix];
char words[wordsNum][wordLen];
int wordLens[wordsNum];
int wordLensOccur[wordsNum];
int wordCount = 0;
coordinate spacesCords[maxSpacelen][max];
int spaceLens[maxSpacelen] = {0};
int spaceCount = 0;
cellCheck cordCheck[gridRowFix][gridColFix];

// check the given char that is not a '*'
int checkCell(int x, int y, char arr[gridRowFix][gridColFix])
{
    if (arr[x][y] != '*')
        return 1;
    return 0;
}

// check a given char is a '#' or '*' or a alpha
int isInValid(char x)
{
    if ((x == '#') || (x == '*') || ((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z')))
        return 0;
    else
        return 1;
}

// check given char is a alpha
int isAplha(char x)
{
    if (((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z')))
        return 1;
    else
        return 0;
}

// check the inputs are valid
int checkInvalidInput()
{
    // check the grid is valid
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            if (isInValid(grid[i][j]))
                return 1;
        }
    }

    // check the words are valid
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

// get the space vertically for a given cell
void updateVertical(int x, int y, char arr[gridRowFix][gridColFix])
{
    /*
        check vertically from cell x,y for spaces and add there 
        coordinates to spaceCord.
        if the length not equal to one, update the spaceLens,
        restore the preverse state
    */

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

// get the space horizontally for a given cell
void updateHorizon(int x, int y, char arr[gridRowFix][gridColFix])
{
    /*
        check horizontally from cell x,y for spaces and add there 
        coordinates to spaceCord.
        if the length not equal to one, update the spaceLens,
        restore the preverse state
    */

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

// define a function to get all spaces in the grid and update the space variables
void updateSpaceVar()
{
    // initialize the cordCheck arr
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            cordCheck[i][j].horiCheck = 1;
            cordCheck[i][j].verCheck = 1;
        }
    }

    // iterate each cell and check for spaces
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            if (checkCell(i, j, grid))
            {
                // if cell didn't horizontally ckecked, then check it
                if (cordCheck[i][j].horiCheck)
                {
                    updateHorizon(i, j, grid);
                }

                // if cell didn't vartically ckecked, then check it
                if (cordCheck[i][j].verCheck)
                {
                    updateVertical(i, j, grid);
                }
            }
        }
    }
}

// function to get the inputs and update the variables
void getInputs()
{
    // get the grid from the user
    gridRow = 0;
    while (1)
    {
        grid[gridRow][0] = '\0';
        fgets(&grid[gridRow][0], gridCol, stdin);

        if (strlen(&grid[gridRow][0]) == 1)
            break;

        gridRow++;
    }

    // get the number of cols
    gridCol = strlen(&grid[0][0]) - 1;

    // get the words from user
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

// function to check two wordLens is a subset a another SpaceLens
int isSubset()
{
    /*
        this function outut 1, if the wordLens arr is a subset of
        spaceLens arr, else return 0
    */

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

// function to print the grid
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

// function to update the word occurances
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

// function to swap two int variable values
void swapInt(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// function to swap two string variable
void swapWords(char arr1[], char arr2[])
{
    char temp[wordLen];
    strcpy(temp, arr1);
    strcpy(arr1, arr2);
    strcpy(arr2, temp);
}

// sort the words with respect to the occurances
void sortWordOccur()
{
    // update the occurances
    updateOccur();

    // sort the wordLens and word
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

// function to place a word in a space in the grid
int word2space(int n, char word[wordLen], coordinate cord[max])
{
    /*
        this function will try to fill the give space by a given word,
        if succeeded return 0,
        else restore the grid and return 1
    */

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

// function to check the grid is filled
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

// main algorithm
int Fill(int arrSpaceLens[], int arrWordLens[])
{
    /*
        A recusive function to solve the puzzel
    */

    // if grid is filled then return 0
    if (checkGridFill())
        return 0;

    // define variables to store current node
    int tempSpaceLens[spaceCount];
    int tempWordLens[wordCount];
    char tempGrid[gridRowFix][gridColFix];
    int temp;
    int temp1;
    // initalize the current node variables
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

    // flag to store a word is filled in the iteration
    int flag = 1;
    // iterate each word in the word arr
    for (int j = 0; j < wordCount; j++)
    {
        if (tempWordLens[j] == -1)
            continue;

        flag = 1;

        // iterate each space in the space arr
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

                // if the word and space are filled, recursive the Fill() function
                if (Fill(tempSpaceLens, tempWordLens))
                {
                    // if the word and space don't match, restore the previese node
                    tempSpaceLens[i] = temp;
                    tempWordLens[j] = temp1;
                    for (int p = 0; p < gridRow; p++)
                    {
                        for (int q = 0; q < gridCol; q++)
                        {
                            grid[p][q] = tempGrid[p][q];
                        }
                    }
                }
            }
        }

        // return 1, if the gives word didn't match any of remaining spaces
        if (flag)
        {
            return 1;
        }
    }

    // return 1. if the grid didn't filled
    if (!checkGridFill())
        return 1;

    return 0;
}

int main()
{
    // get the inputs
    getInputs();

    // check there are any invalid inputs
    if (checkInvalidInput())
    {
        printf("INVALID INPUT\n");
        return 0;
    }

    // get the spaces in the grid
    updateSpaceVar();

    // check the puzzel can solve for given word and spaces
    if (isSubset() == 0)
    {
        printf("IMPOSSIBLE\n");
        return 0;
    }

    // sort the word according to occurances
    sortWordOccur();
    // called the Fill()
    Fill(spaceLens, wordLens);

    // check the puzzel is solved
    if (checkGridFill())
        printGrid();
    else
        printf("IMPOSSIBLE\n");

    return 0;
}