/*
        CO222 - Programming methodology
        Project - Phase 1
        Solve the crossword puzzle using static allocation of arrays

        Group-31

        Group members - E/19/129 K.H. GUNAWARDANA
                        E/19/408 S.J. UBAYASIRI 
*/

// import the libary
#include <stdio.h>
#include <string.h>
#include <time.h>

// define the macros
#define gridRowFix 20
#define gridColFix 20
#define wordsNum 30
#define wordLen 10
#define maxSpacelen 30
#define maxSpace 20

// define a struct to store whether the particular cell is checked vertically and horizontally for adjacent spaces
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

/*
    define the global variables
        grid - store the grid
        words - store the words
        wordLens - store the length of the words
        wordCount - word count
        spacesCords - store the spaces coordinates together
        spaceLens - legths arr of spaces
        spaceCount - count of spaces

*/
char grid[gridRowFix][gridColFix];
char words[wordsNum][wordLen];
int wordLens[wordsNum];
int wordCount = 0;
coordinate spacesCords[maxSpacelen][maxSpace];
int spaceLens[maxSpacelen] = {0};
int spaceCount = 0;
int flag = 0;
// initalize row and col
int gridRow = gridColFix;
int gridCol = gridColFix;

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
            // capitalize rule for the words
            // else
            //     words[i][j] = (('a' <= words[i][j]) && ('z' >= words[i][j])) ? (words[i][j] - 'a' + 'A') : words[i][j];
        }
    }

    return 0;
}

// get the space vertically for a given cell
void updateVertical(int x, int y, char arr[gridRowFix][gridColFix], cellCheck cordCheck[gridRow][gridCol])
{
    /*
        check vertically from cell x,y for spaces and add there 
        coordinates to spaceCord.
        if the length not equal to one, update the spaceLens,
        restore the previous state
    */

    int i = 0;
    while (x < gridRow)
    {
        if (checkCell(x, y, arr)) //cell will only be checked if it is not checked before to  avoid duplicating same space coordinates
        {
            spacesCords[spaceCount][i].x = x;
            spacesCords[spaceCount][i].y = y;

            cordCheck[x][y].verCheck = 0;
            i++;
        }
        else
            break;
        x++;
    }

    if (i != 1) //if length is greatr than 1 add the length of the space to the space length array
    {
        spaceLens[spaceCount] = i;
        spaceCount++;
    }
    else
    { //otherwise restoring the space coordinate array to the previous state because space with length 1 is not a valid space
        spacesCords[spaceCount][0].x = -1;
        spacesCords[spaceCount][0].y = -1;
    }
}

// get the space horizontally for a given cell
void updateHorizon(int x, int y, char arr[gridRowFix][gridColFix], cellCheck cordCheck[gridRow][gridCol])
{
    /*
        check horizontally from cell x,y for spaces and add there 
        coordinates to spaceCord.
        if the length not equal to one, update the spaceLens,
        restore the preverse state
    */

    int i = 0;
    while (y < gridCol)
    {
        if (checkCell(x, y, arr)) //cell will only be checked if it is not checked before to  avoid duplicating same space coordinates
        {
            spacesCords[spaceCount][i].x = x;
            spacesCords[spaceCount][i].y = y;

            cordCheck[x][y].horiCheck = 0; //cell doesn't need to be checked again
            i++;
        }
        else
            break;
        y++;
    }

    if (i != 1) //if length is greatr than 1 add the length of the space to the space length array
    {
        spaceLens[spaceCount] = i;
        spaceCount++;
    }
    else
    { //otherwise restoring the space coordinate array to the previous state because space with length 1 is not a valid space
        spacesCords[spaceCount][0].x = -1;
        spacesCords[spaceCount][0].y = -1;
    }
}

// define a function to get all spaces in the grid and update the space variables
void updateSpaceVar()
{
    // define the coordinate check arr
    cellCheck cordCheck[gridRow][gridCol];

    // initialize the cordCheck arr
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            //initializing all elements to 1(initially all cells need to be checked both horizontally and vetically)
            cordCheck[i][j].horiCheck = 1;
            cordCheck[i][j].verCheck = 1;
        }
    }

    // iterate each cell and check for spaces
    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            if (checkCell(i, j, grid) && (spaceCount < maxSpacelen)) //if the cell is not a * and the space count is less than the space array length
            {
                // if cell didn't horizontally checked, then check it
                if (cordCheck[i][j].horiCheck)
                {
                    updateHorizon(i, j, grid, cordCheck);
                }

                // if cell didn't vartically checked, then check it
                if (cordCheck[i][j].verCheck)
                {
                    updateVertical(i, j, grid, cordCheck);
                }
            }
        }
    }
}

// function to get the inputs and update the variables
int getInputs()
{
    // get the grid from the user
    gridRow = 0;
    int temp = 0;
    while (1)
    {
        // get the grid row by row
        grid[gridRow][0] = '\0';
        fgets(&grid[gridRow][0], gridCol, stdin);

        if (strlen(&grid[gridRow][0]) == 1)
            break;

        // check the row length is equal
        // if not invalid input
        if (gridRow == 0)
            temp = strlen(&grid[gridRow][0]);
        else if (temp != strlen(&grid[gridRow][0]))
            return 1;

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

        //getting the worrd lengths and uupdating the word length array
        wordLens[wordCount] = strlen(&words[wordCount][0]) - 1;
        wordCount++;
    }

    return 0;
}

// function to check whether the word length array is a subset of space length array. Otherwise the grid is impossible to fill
int isSubset()
{
    /*
        this function output 1, if the wordLens arr is a subset of
        spaceLens arr, else return 0
    */

    // if the number of words is greater than the number of spaces, the grid is impossible to fill
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
        // check all the space length array to find a space with length equal to the i th word length
        for (int j = 0; j < spaceCount; j++)
        {
            if (wordLens[i] == arrTemp[j])
            { // if there is a space with length equal to word length, then flag is set to 0
                flag = 0;
                arrTemp[j] = -1;
                break;
            }
        }
        //if there is not a space that is equal to the word length, grid  is impossible
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

// function to update the word occurances(number of words with same length)
void updateOccur(int wordLensOccur[], int wordLens[])
{
    int tempArr[wordCount]; // copy of the word length array
    int count;

    //copying array
    for (int i = 0; i < wordCount; i++)
    {
        tempArr[i] = wordLens[i];
    }

    //check whether the word is counted before
    for (int i = 0; i < wordCount; i++)
    {
        count = 0;
        if (tempArr[i] == -2)
            continue;

        for (int j = 0; j < wordCount; j++)
        { //counting the number of words with same word length
            if (wordLens[i] == tempArr[j])
            {
                count++;
                tempArr[j] = -2;
            }
        }

        for (int j = 0; j < wordCount; j++)
        {
            //managing an array of occurances of words with same length
            if (wordLens[j] == wordLens[i])

            {
                //in word length occurances array, i th element is the number of occurances of words with same length as i th word.
                //this array is used to sort the word array according to the occurances of words with same length
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
//we start to fill the grid with word that has minimum occurances of words of the same length.
//That is to simplify the tree of instances of the grid
void sortWordOccur(int wordLens[], char words[wordsNum][wordLen])
{
    int wordLensOccur[wordCount];

    // update the occurances
    updateOccur(wordLensOccur, wordLens);

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
int word2space(int n, char word[], coordinate cord[])
{
    /*
        this function will try to fill the give space by a given word,
        if succeeded return 0,
        else restore the grid and return 1
    */

    char tempGrid[gridRow][gridCol]; //get a copy of previous state to restore if necessary

    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            tempGrid[i][j] = grid[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    { // fill the word
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
                    grid[i][j] = tempGrid[i][j]; // restore the grid
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

// check to -1 is in a given array
//to check whether all words are filled
int checkWordsAll(int arr[])
{
    for (int i = 0; i < wordCount; i++)
    {
        if (arr[i] != -1)
            return 0;
    }
    return 1;
}

// main algorithm
int Fill(int arrSpaceLens[], int arrWordLens[])
{
    /*
        A recusive function to solve the puzzel
    */

    // base case of the recursion. If the grid is filled then return 0
    if (checkGridFill())
    {
        if (checkWordsAll(arrWordLens)) // if there are words left, then flag will remain 0
            flag = 1;
        return 0;
    }

    // define variables to store current node
    int tempSpaceLens[spaceCount];
    int tempWordLens[wordCount];
    char tempGrid[gridRow][gridCol];
    int temp;
    int temp1;

    // initalize the current node variables
    // get copies the current instances of grid, word length and space length to restore is necessary
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

    // iterate each word in the word arr
    for (int j = 0; j < wordCount; j++)
    {
        if (tempWordLens[j] == -1) // if the word is filled, j th element is -1
            continue;

        // iterate each space in the space arr
        for (int i = 0; i < spaceCount; i++)
        {
            if (tempSpaceLens[i] == -1) // if the i space is filled with a word, i the element is -1
                continue;

            if (tempSpaceLens[i] == tempWordLens[j] && (word2space(tempSpaceLens[i], &words[j][0], &spacesCords[i][0]) == 0))
            {
                // get word length and space because
                //even if the word could be filled, if there's a dead end further down on the tree, a restoring would be required
                temp = tempSpaceLens[i];
                temp1 = tempWordLens[j];

                // if the word could be filled, set the word and space to -1 to indicate it is filled
                tempSpaceLens[i] = -1;
                tempWordLens[j] = -1;

                // if the word and space are filled, recursive the Fill() function
                // go to the next node of the tree until base condition is satisfied
                //(fill function returns 1 if base case is not satisfied)
                // if the next word cannot be filled to the current grid,
                //then this conditional statement will be executed to restore the previous node
                if (Fill(tempSpaceLens, tempWordLens))
                {
                    // if the word and space don't match, restore the previous node
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

        // check the grid is filled
        if (!checkGridFill())
            return 1;
    }

    return 0;
}

// main function
int main()
{
    printf("\nOuput >>> \n");
    clock_t t;
    t = clock();

    // get the inputs
    // check there are any invalid inputs
    if (getInputs() || checkInvalidInput())
    {
        printf("INVALID INPUT\n");
        return 0;
    }

    // get the spaces in the grid
    updateSpaceVar();

    // check the puzzel can solve for given word and spaces
    if (!isSubset())
    {
        printf("IMPOSSIBLE\n");
        return 0;
    }

    // sort the word according to occurances
    sortWordOccur(wordLens, words);

    // called the Fill()
    // check the whether puzzel is solved
    //Fill() return 0 if the grid is filled and flag=1 if all words are filled
    if (!Fill(spaceLens, wordLens) && flag)
        printGrid();
    else
        printf("IMPOSSIBLE\n");

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Time - %f(seconds)\n\n", time_taken);

    return 0;
}