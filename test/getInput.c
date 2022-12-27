#include <stdio.h>
#include <string.h>

#define gridRow 4
#define gridCol 4
#define wordsNum 16
#define wordLen 10

void getInputs(char grid[gridRow][gridCol], char words[wordsNum][wordLen], int wordsLens[wordsNum], int *count)
{
    for (int i = 0; i < gridRow; i++)
    {
        scanf("%[^\n]%*c\n", &grid[i][0]);
    }

    while (*count < wordsNum)
    {
        words[*count][0] = '\0';
        fgets(&words[*count][0], wordLen, stdin);

        if (strlen(&words[*count][0]) == 1)
            break;

        (*count)++;
    }
}

int main()
{

    char grid[gridRow][gridCol];
    char words[wordsNum][wordLen];
    int wordsLens[wordsNum] = {0};
    int count = 0;

    getInputs(grid, words, wordsLens, &count);

    for (int i = 0; i < count; i++)
    {
        wordsLens[i] = strlen(&words[i][0]);
    }

    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < count; i++)
    {
        printf("%s", &words[i][0]);
    }

    return 0;
}