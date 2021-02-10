#include <stdio.h>
#include "baseOps.h"

#define SIZE 500000

int ** forceBrute(int ** houses, int ** critPoints)
{
    int ** arr = (int **)malloc(SIZE * 2 * sizeof(int *)); 
    for (int i = 0; i < SIZE * 2; i++)
    {
        arr[i] = (int *)malloc(2 * sizeof(int)); 
    }

    int row = 0;
    for(int i = 0; i < SIZE * 2; ++i)
    {
        int * critPoint = critPoints[i];
        int height = critPoint[Y];

        for(int j = 0; j < SIZE; ++j)
        {
            int * house = houses[j];

            if(house[L] < critPoint[X] && critPoint[X] < house[R] && height < house[H])
            {
                height = house[H];
            }
        }

        arr[row][X] = critPoint[X];
        arr[row++][Y] = height;
    }

    quickSort(arr, 0, (SIZE * 2) - 1);

    return filter(arr, SIZE);
}

int main(void)
{
    int ** houses = readFile("../data/N500000_0");

    int ** critPoints = extractCritPoint(houses, SIZE);

    int ** solution = forceBrute(houses, critPoints);

    int max = solution[1][0];
    printf("%d\n", solution[0][0]);
    for (int i = 2; i < solution[0][0]; i++)
    {
        if(solution[i][0] < max)
        {
            printf("%d\n", solution[i][0]);
            break;
        }
        max = solution[i][0];
    }

    for (int i = 0; i < SIZE; i++)
    {
        free(houses[i]);
    }
    free(houses);

    for (int i = 0; i < SIZE  * 2; i++)
    {
        free(critPoints[i]);
    }
    free(critPoints);

    int solSize = solution[0][0];
    for (int i = 0; i < solSize; i++)
    {
        free(solution[i]);
    }
    free(solution);

    return 0;
}