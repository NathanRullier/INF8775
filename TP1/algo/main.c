#include "allAlgo.h"

int main(int argc, char * argv[])
{
    char data[100] = "../data/";
    char * number = "0";
    if(argc == 1)
    {
        strcat(data, "N1000_0");
    }
    else
    {
        strcat(data, argv[1]);
        if(argc >= 3)
        {
            number = argv[2];
        }
    }

    CriticalPoints houses = readFile(data);

    CriticalPoints critPoints = extractCritPoint(&houses);

    CriticalPoints solution = diviserReigner(&critPoints, strtol(number, NULL, 10));

    int * last = solution.points[0];
    printf("%d\n", solution.size);
    int f = 0;
    for (int i = 1; i < solution.size; i++)
    {
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

    free(solution.points);

    return 0;
}