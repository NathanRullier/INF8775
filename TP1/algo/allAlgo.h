#include <stdio.h>
#include "baseOps.h"

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

CriticalPoints diviserReigner(CriticalPoints * critPoints, int limit)
{
    if (critPoints->size < 4)
    {
        return *critPoints;
    } 
    else if (critPoints->size <= limit)
    {
        return forceBrute(critPoints);
    }

    int newSizeL = critPoints->size / 2;
    int newSizeR = critPoints->size / 2;
    if(newSizeL % 2 == 1)
    {
        newSizeL ++;
        newSizeR --;
    }

    CriticalPoints left;
    left.size = newSizeL;
    left.low = critPoints->low;
    left.points = critPoints->points;
    left.houses = critPoints->houses;

    CriticalPoints right;
    right.size = newSizeR;
    right.low = left.low + left.size;
    right.points = critPoints->points;
    right.houses = critPoints->houses;

    if(critPoints->size > 4)
    {
        left = diviserForce(&left, limit);
        right = diviserForce(&right, limit);
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
        // printf("%d\n",i);
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

    CriticalPoints cp;
    cp.size = nbCritFinal;
    cp.low = 0;
    cp.points = critArr;
    return cp;
}