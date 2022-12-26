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
    int count = 0;

    for (int i = 0; i < gridRow; i++)
    {

        scanf("%[^\n]%*c\n", &grid[i][0]);
    }

    scanf("%c", &temp);

    while (count < wordsNum)
    {
        words[count][0] = '\0';
        fgets(&words[count][0], wordLen, stdin);

        if (strlen(&words[count][0]) == 1)
            break;

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