#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 0
#define R 1
#define H 2
#define X 0
#define Y 1

typedef enum {false, true} bool;

struct CriticalPoints
{
    int size;
    int low;
    int ** points;
};


struct CriticalPoints readFile(char const * fileName)
{
    FILE* file = fopen(fileName, "r"); 
    char line[256];

    bool first = true;
    int **arr = NULL;

    struct CriticalPoints cp;

    int row = -1;

    while (fgets(line, sizeof(line), file))
    {
        char * pch;
        int col = 0;
        pch = strtok (line," ,.-");
        while (pch != NULL)
        {
            int x = atoi(pch);

            if(first)
            {
                arr = (int **)malloc(x * sizeof(int *)); 
                cp.size = x;
                for (int i=0; i<x; i++)
                {
                    arr[i] = (int *)malloc(3 * sizeof(int)); 
                }
                first = false;
            }
            else
            {
                arr[row][col] = x;
                col++;
            }
            pch = strtok (NULL, " ,.-");
        }
        row++;
    }

    fclose(file);

    cp.points = arr;
    // cp.size = 10;
    return cp;
}

struct CriticalPoints extractCritPoint(struct CriticalPoints houses)
{
    int ** arr = (int **)malloc(houses.size * 2 * sizeof(int *)); 
    for (int i = 0; i < houses.size * 2; i++)
    {
        arr[i] = (int *)malloc(2 * sizeof(int)); 
    }

    int row = 0;
    for(int i = 0; i < houses.size; i++)
    {
        arr[row][X] = houses.points[i][L];
        arr[row][Y] = houses.points[i][H];
        arr[++row][X] = houses.points[i][R];
        arr[row++][Y] = 0;
    }

    struct CriticalPoints cp;
    cp.size = row;
    cp.points = arr;

    return cp;
}

struct CriticalPoints filter(int ** solution, int size)
{
    int ** arr = (int **)malloc(size * sizeof(int *)); 
    
    int* lastSolution = solution[0];

    int row = 0;
    arr[row++] = solution[0];

    for(int i = 1; i < size; ++i)
    {
        if(solution[i][X] != lastSolution[X] && solution[i][Y] != lastSolution[Y])
        {
            arr[row++] = solution[i];
            lastSolution = solution[i];
        }
        else
        {
            free(solution[i]);
        }
    }

    int ** finalArr = (int **)malloc(row * sizeof(int *));

    for (int i = 0; i < row; i++)
    {
        finalArr[i] = arr[i]; 
    }

    free(arr);
    free(solution);

    struct CriticalPoints cp;
    cp.size = row;
    cp.points = finalArr;

    return cp;
}

void swap(int ** a, int ** b)  
{  
    int *t = *a;  
    *a = *b;  
    *b = t;  
}  
  
int partition (int ** arr, int low, int high)
{  
    int pivot = arr[high][X]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j][X] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        } 
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  
void quickSort(int ** arr, int low, int high)  
{  
    if (low < high)  
    {  
        int pi = partition(arr, low, high);  
  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  
  