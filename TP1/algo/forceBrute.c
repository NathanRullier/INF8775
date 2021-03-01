#include "allAlgo.h"

CriticalPoints forceBrute(CriticalPoints * critPoints)
{
    int ** arr = (int **)malloc(critPoints->size * sizeof(int *)); 
    for (int i = 0; i < critPoints->size; i++)
    {
        arr[i] = (int *)malloc(2 * sizeof(int)); 
    }

    int row = 0;
    for(int i = critPoints->low; i < critPoints->low + critPoints->size; i++)
    {
        int * critPoint = critPoints->points[i];
        int height = critPoint[Y];

        for(int j = critPoints->low / 2; j < (critPoints->low + critPoints->size) / 2; j++)
        {
            int * house = critPoints->houses->points[j];
            if(house[L] <= critPoint[X] && critPoint[X] < house[R] && height < house[H])
            {
                height = house[H];
            }
        }

        arr[row][X] = critPoint[X];
        arr[row++][Y] = height;
    }

    quickSort(arr, 0, critPoints->size - 1);

    return filter(arr, critPoints->size);
}

int main(void)
{
    CriticalPoints houses = readFile("../data/N5000_0");

    CriticalPoints critPoints = extractCritPoint(&houses);

    CriticalPoints solution = forceBrute(&critPoints);
    
    int * last = solution.points[0];
    printf("%d\n", solution.size);
    int f = 0;
    for (int i = 1; i < solution.size; i++)
    {
        printf("x = %d, y = %d\n", solution.points[i][X], solution.points[i][Y]);
        if(solution.points[i][X] == last[X] || solution.points[i][Y] == last[Y])
        {
            f++;
        }
        last = solution.points[i];
    }
    printf("%d\n", f);

    for (int i = 0; i < houses.size; i++)
    {
        free(houses.points[i]);
    }
    free(houses.points);

    for (int i = 0; i < critPoints.size; i++)
    {
        free(critPoints.points[i]);
    }
    free(critPoints.points);

    for (int i = 0; i < solution.size; i++)
    {
        free(solution.points[i]);
    }
    free(solution.points);

    return 0;
}