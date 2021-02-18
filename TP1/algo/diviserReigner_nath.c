#include <stdio.h>
#include "baseOps.h"

int g = 0;

struct CriticalPoints diviserReigner(struct CriticalPoints critPoints)
{
    if (critPoints.size < 4)
    {
        return critPoints;
    }
    int newSizeL = critPoints.size / 2;
    int newSizeR = critPoints.size / 2;
    if(newSizeL % 2 == 1)
    {
        newSizeL ++;
        newSizeR --;
    }

    struct CriticalPoints left;
    left.size = newSizeL;
    left.low = critPoints.low;
    left.points = critPoints.points;

    struct CriticalPoints right;
    right.size = newSizeR;
    right.low = left.low + left.size;
    right.points = critPoints.points;

    if(critPoints.size > 4)
    {
        left = diviserReigner(left);
        right = diviserReigner(right);
    }
    int size = left.size + right.size;
    int ** critArrTmp = (int **)malloc(size * sizeof(int *));

    int h1 = 0;
    int h2 = 0;
    int hCur = 0;
    int hLast = 0;

    int l = left.low;
    int r = right.low;
    int nbCrit = 0;
    bool endR = false;
    // printf("l %d\n",left.size);
    // printf("r %d\n",right.size);

    for(int i = 0; i < size ; i++)
    {
        if(l < left.low + left.size && left.points[l][X] < right.points[r][X])
        {
        // printf("lxy %d %d\n",left.points[l][X],left.points[l][Y]);
            h1 = left.points[l][Y];
            hCur = h1;
            if(h2 >= hCur)
            {
                hCur = h2;
                if(hCur < hLast)
                {
                    left.points[l][Y] = hCur;
                    critArrTmp[nbCrit++] = left.points[l];
                }
            }
            else
            {
                critArrTmp[nbCrit++] = left.points[l];
            }

            l += l == left.low + left.size? 0 : 1;
        }
        else if (r < right.low + right.size && !endR)
        {
        // printf("rxy %d %d\n",right.points[r][X],right.points[r][Y]);
            h2 = right.points[r++][Y];
            hCur = h2;
            if(h1 >= hCur)
            {
                hCur = h1;
                if(hCur < hLast)
                {
                    right.points[r - 1][Y] = hCur;
                    critArrTmp[nbCrit++] = right.points[r - 1];
                }
            }
            else
            {
                critArrTmp[nbCrit++] = right.points[r - 1];
            }
            if(r == right.low + right.size){r--; endR = true;};
        }
        else 
        {
            h1 = left.points[l][Y];
            hCur = h1;
            if(h2 >= hCur)
            {
                hCur = h2;
                if(hCur < hLast)
                {
                    left.points[l][Y] = hCur;
                    critArrTmp[nbCrit++] = left.points[l];
                }
            }
            else
            {
                critArrTmp[nbCrit++] = left.points[l];
            }

            l += l == left.low + left.size? 0 : 1;
        }
        hLast = hCur;
   }
    
    int ** critArr = (int **)malloc(nbCrit * sizeof(int *));

    for (int i = 0; i < nbCrit; i++)
    {
        critArr[i] = critArrTmp[i]; 
    }
    free(critArrTmp);

    struct CriticalPoints cp;
    cp.size = nbCrit;
    cp.low = 0;
    cp.points = critArr;
    return cp;
}


int main(void)
{
    struct CriticalPoints houses = readFile("../data/N1000_0");

    struct CriticalPoints critPoints = extractCritPoint(houses);

    struct CriticalPoints solution = diviserReigner(critPoints);

    int max = solution.points[0][X];
    printf("%d\n", solution.size);
    int f = 0;
    for (int i = 0; i < solution.size; i++)
    {
        // printf("x = %d, y = %d\n", solution.points[i][X], solution.points[i][Y]);
        if(solution.points[i][X] < max)
        {
            f++;
        }
        max = solution.points[i][X];
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