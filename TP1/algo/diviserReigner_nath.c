#include <stdio.h>
#include "baseOps.h"

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
    bool lEnd = false;
    bool rEnd = false;

    for(int i = 0; i < size ; i++)
    {
        if(left.points[l][X] == right.points[r][X])
        {
            h1 = left.points[l][Y];
            h2 = right.points[r][Y];
            critArrTmp[nbCrit++] = h1 > h2 ? left.points[l] : right.points[r];
            hCur = h1 > h2 ? h1 : h2;
            
            i++;
            r++;
            if(r == right.low + right.size){r--; rEnd = true;}
            l++;
            if(l == left.low + left.size){l--; lEnd = true;}
        }
        else if(!lEnd && (rEnd || left.points[l][X] < right.points[r][X]))
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
            l++;
            if(l == left.low + left.size){l--; lEnd = true;}
        }
        else
        {
            h2 = right.points[r][Y];
            hCur = h2;
            if(h1 >= hCur)
            {
                hCur = h1;
                if(hCur < hLast)
                {
                    right.points[r][Y] = hCur;
                    critArrTmp[nbCrit++] = right.points[r];
                }
            }
            else
            {
                critArrTmp[nbCrit++] = right.points[r];
            }
            r++;
            if(r == right.low + right.size){r--; rEnd = true;}
        }
        hLast = hCur;
   }
    
    int ** critArr = (int **)malloc(nbCrit * sizeof(int *));
    critArr[0] = critArrTmp[0]; 
    int nbCritFinal=1;
    for (int i = 1; i < nbCrit; i++)
    {
        if(critArrTmp[i][X] != critArrTmp[i-1][X] )
        {
            critArr[nbCritFinal] = critArrTmp[i];
            nbCritFinal++;
        }
    }
    free(critArrTmp);

    struct CriticalPoints cp;
    cp.size = nbCritFinal;
    cp.low = 0;
    cp.points = critArr;
    return cp;
}


int main(void)
{
    struct CriticalPoints houses = readFile("../data/N1000_0");

    struct CriticalPoints critPoints = extractCritPoint(houses);

    struct CriticalPoints solution = diviserReigner(critPoints);

    int * last = solution.points[0];
    printf("%d\n", solution.size);
    int f = 0;
    for (int i = 1; i < solution.size; i++)
    {
        // printf("x = %d, y = %d\n", solution.points[i][X], solution.points[i][Y]);
        if(solution.points[i][X] == last[X] || solution.points[i][Y] == last[Y])
        {
            printf("%d\n",i);
            printf("%d %d\n",last[X], last[Y]);
            printf("%d %d\n\n",solution.points[i][X], solution.points[i][Y]);
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