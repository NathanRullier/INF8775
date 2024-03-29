#include "allAlgo.h"
#include <time.h>
int main(int argc, char * argv[])
{
    char data[200] = "";
    bool gotE = false;
    bool gotA = false;

    char algo[10] = "";

    bool showTime = false;
    bool showPoints = false;

    for(int i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "-a"))
        {
            gotA = true;
            strcpy(algo, argv[++i]);
        }
        else if(!strcmp(argv[i], "-t"))
        {
            showTime = true;
        }
        else if(!strcmp(argv[i], "-p"))
        {
            showPoints = true;
        }
        else if(!strcmp(argv[i], "-e"))
        {
            gotE = true;
            strcat(data, argv[++i]);
        }
    }

    if(!gotE)
    {
        printf("Vous devez entrer un chemin (-e CHEMIN_EXEMPLAIRE)\n");
        return 1;
    }
    if(!gotA)
    {
        printf("Vous devez entrer un type d'algorithme (-a {brute, recursif, seuil})\n");
        return 1;
    }

    CriticalPoints houses = readFile(data);

    CriticalPoints critPoints = extractCritPoint(&houses);

    int number = 0;
    if(argc >= 2)
    {
        if(!strcmp(algo, "brute"))
        {
            number = critPoints.size;
        }
        else if(!strcmp(algo, "seuil"))
        {
            number = 8;
        }
    }

    clock_t start = clock();
    CriticalPoints solution = diviserReigner(&critPoints, number);
    clock_t end = clock();

    if(showPoints)
    {
        for (int i = 0; i < solution.size; i++)
        {
            printf("%d %d\n", solution.points[i][X], solution.points[i][Y]);
        }
    }

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

    double cpuTimeUsed = 0;
    if(showTime){
        cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
        printf("%f\n", cpuTimeUsed);
    }

    return cpuTimeUsed;
}
