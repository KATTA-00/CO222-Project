#include <stdio.h>

typedef struct _
{
    int horiCheck;
    int verCheck;
} coord;

int main()
{

    char arr[4][4] = {{'#', '#', '*', '#'},
                      {'#', '#', '*', '#'},
                      {'#', '*', '*', '*'},
                      {'#', '#', '*', '#'}};

    coord cordCheck[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c ", arr[i][j]);
            cordCheck[i][j].horiCheck = 0;
            cordCheck[i][j].verCheck = 0;
        }
        printf("\n");
    }

    int count = 0;
    int x, y;
    int horiSearch[10][2];
    int vertSearch[10][2];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            count = 0;
            if (arr[i][j] == '*')
            {
                x = i;
                y = j;
                count++;
            }
        }
    }

    return 0;
}