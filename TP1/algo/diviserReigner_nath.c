#include <stdio.h>
#include "baseOps.h"

#define SIZE 5000

int ** diviserReigner(int ** critPoints, int low, int high)
{
    int ** left;
    int ** right;

    if(high - low > 4)
    {
        left = diviserReigner(critPoints, low, high / 2 - low / 2);
        right = diviserReigner(critPoints, high / 2 - low / 2 + 1, high);
    } 
    else
    {
        left = (int **)malloc(2 * sizeof(int *));
        left[0] = critPoints[low];
        left[1] = critPoints[low + 1];

        right = (int **)malloc(2 * sizeof(int *));
        right[0] = critPoints[high - 1];
        right[1] = critPoints[high];
    }
    
    int ** critArrTmp = (int **)malloc((high - low) * sizeof(int *)); 
    int h1 = 0;
    int h2 = 0;
    int hCur;

    int l = 0;
    int r = 0;

    for(int i = 0; i <= high - low; i++)
    {
        if(left[l][X] < right[r][X])
        {
            hCur = left[l++][Y];
            if(h2 < hCur)
            {
                h1 = hCur;
            }
        }
        else
        {
            hCur = left[r++][Y];
            if(h1 < hCur)
            {
                h2 = hCur;
            }
        }
    }
}


int main(void)
{
    int ** houses = readFile("../data/N5000_4");

    int ** critPoints = extractCritPoint(houses, SIZE);

    int ** solution = diviserReigner(critPoints, 0, SIZE  * 2 - 2);

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