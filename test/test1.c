#include <stdio.h>
#include <string.h>

#define gridRow 4
#define gridCol 4
#define wordsNum 16
#define wordLen 10

int main()
{

    char grid[gridRow][gridCol];
    char temp;
    char words[wordsNum][wordLen];
    char word[wordLen];
    int count = 0;

    for (int i = 0; i < gridRow; i++)
    {
        for (int j = 0; j < gridCol; j++)
        {
            scanf("%c", &grid[i][j]);
        }
        scanf("%c", &temp);
    }

    scanf("%c", &temp);

    while (1)
    {
        word[0] = '\0';
        fgets(word, wordLen, stdin);

        if (strlen(word) == 0)
            break;

        strcpy(&words[count][0], word);
        count++;
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