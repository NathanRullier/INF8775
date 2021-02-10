#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

int ** readFile(char const * fileName)
{
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[256];

    bool first = true;
    int **arr = NULL;

    int row = -1;

    while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        char * pch;
        int col = 0;
        pch = strtok (line," ,.-");
        while (pch != NULL){
            int x = atoi(pch);

            if(first){
                arr = (int **)malloc(x * sizeof(int *)); 
                for (int i=0; i<x; i++) {
                    arr[i] = (int *)malloc(3 * sizeof(int)); 
                }
                first = false;
            }
            else{
                arr[row][col] = x;
                col++;
            }
            pch = strtok (NULL, " ,.-");
        }
        row++;
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

    return arr;
}