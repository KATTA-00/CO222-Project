#include <stdio.h>
#include <string.h>

#define gridRow 4
#define gridCol 4
#define wordsNum 16
#define wordLen 10

void swapWords(char arr1[], char arr2[])
{
    char temp[wordLen];
    strcpy(temp, arr1);
    strcpy(arr1, arr2);
    strcpy(arr2, temp);
}

int main()
{

    char arr1[] = "asdw";
    char arr2[] = "kans";

    swapWords(arr1, arr2);

    printf("%s - %s\n", arr1, arr2);

    return 0;
}