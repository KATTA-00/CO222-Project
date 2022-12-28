#include <stdio.h>

int arr1[] = {4, 3};
int arr1len = 2;
int arr2[] = {3, 4, 2, 1};
int arr2len = 4;

int isSubset()
{
    int arrTemp[arr2len];
    for (int i = 0; i < arr2len; i++)
    {
        arrTemp[i] = arr2[i];
    }

    int flag = 0;
    for (int i = 0; i < arr1len; i++)
    {
        flag = 1;
        for (int j = 0; j < arr2len; j++)
        {
            if (arr1[i] == arrTemp[j])
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

int main()
{
    printf("%d", isSubset());
    return 0;
}
