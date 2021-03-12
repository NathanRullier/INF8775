#include "allAlgo.h"
#include <algorithm>
#include <bitset> 

vector<vector<double>> getSimpleDistanceVector(vector<XY> & points, vector<int> & S);
void getDistanceVector(vector<vector<double>> & D, vector<int> & S, int size, int precSize);
vector<XY> getFinalDistance(vector<XY> & points, vector<vector<double>> & D, vector<int> & S, int size);

vector<int> getSize(int n)
{
    vector<int> size;
    for (size_t i = 0; i <= n; i++)
    {
        for (size_t j = i; j > 1; j--)
        {
            size[j-1] += size[j-2]; 
        }
        
        size.push_back(1);
    }
    size.erase(size.begin());
    size.pop_back();

    return size;
}

void setS(vector<int> & tmp, vector<int> & S, vector<int> & num, int k, int offset = 0)
{
    if (k == 0) {
        S.push_back(1 << tmp[0]);
        for (size_t i = 1; i < tmp.size(); i++)
        {
                S.back() |= 1 << tmp[i];    
        }
        return;
    }
    for (int i = offset; i <= num.size() - k; i++) {
        tmp.push_back(num[i]);
        setS(tmp, S, num, k-1, i+1);
        tmp.pop_back();
    }
}

vector<XY> dynamique(vector<XY> & points)
{
    vector<int> num;
    for (int i = 0; i < points.size() - 1; i++)
    {
        num.push_back(i);
    }

    vector<int> S;
    for (size_t i = 1; i < num.size(); i++)
    {
        vector<int> tmp;
        setS(tmp, S, num, i);
    }

    vector<int> size = getSize(points.size() - 1);
    vector<vector<double>> D = getSimpleDistanceVector(points, S);

    int curSize = 0;
    for (size_t i = 1; i < size.size(); i++)
    {
        curSize += size[i];
        getDistanceVector(D, S, size[i], curSize);
    }

    return getFinalDistance(points, D, S, size.back());
}

vector<vector<double>> getSimpleDistanceVector(vector<XY> & points, vector<int> & S)
{
    vector<vector<double>> D;

    int rowSize = points.size();
    int colSize = pow(2, rowSize - 1);

    for(int i = 1; i < rowSize; i++)
    {
        vector<double> di(S.size() + 1);
        
        for (size_t j = 0; j < rowSize; j++)
        {
            double toAdd = -1;
            if(!(S[i - 1] & (1 << (j - 1))))
            {
                toAdd = sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2));
            }
            di[j] = toAdd;
        }

        D.push_back(di);
    }

    return D;
}

vector<int> findBitPosition(int n) 
{ 
    vector<int> posVec;
    int pos = 0;
  
    while (n) { 
        if(n & 1)
        {
            posVec.push_back(pos);
        }

        n = n >> 1; 
        pos++; 
    } 
  
    return posVec; 
} 

void getDistanceVector(vector<vector<double>> & D, vector<int> & S, int size, int precSize)
{
    int rowSize = D.size();
    int colSize = precSize + size;
    
    
    for(int i = precSize - 1; i <= colSize; i++)
    {
        vector<int> pos = findBitPosition(S[i - 1]);

        for (size_t j = 0; j < rowSize; j++)
        {
            double toAdd = -1;
            if(!(S[i - 1] & (1 << j)))
            {
                vector<double> results;
                int top = pos.size() - 1;
                for (int k = 0; k < pos.size(); k++)
                {
                    int si = S[i - 1] & ~(1UL << pos[k]);
                    int col = 0;
                    while(S[col] != si)
                    {
                        col++;
                    }
                    if(top == k)
                    {
                        top--;
                    }
                    if(D[pos[k]][col + 1] != -1)
                    {
                        results.push_back(D[pos[k]][col + 1] + D[pos[top]][0]);
                    }
                }
                double smallest = -1;
                for (size_t d = 0; d < results.size(); d++)
                {
                    if(smallest == -1 || smallest > results[d]){smallest = results[d];}
                }
                
                toAdd = smallest;
            }
            
            D[j][i] = toAdd;
        }
    }
}

vector<XY> getFinalDistance(vector<XY> & points, vector<vector<double>> & D, vector<int> & S, int size)
{
    double smallest = -1;
    int idxISmallest = 0;
    int idxJSmallest = 0;
    for (size_t i = 0; i < D.size(); i++)
    {
        for (size_t j = D[i].size() - size; j < D[i].size(); j++)
        {
            if(D[i][j] != -1)
            {
                double val = D[i][j] + D[i][0];
                if(smallest == -1 || smallest > val)
                {
                    smallest = val; 
                    idxISmallest = i;
                    idxJSmallest = j;
                }
            }  
        }      
    }
    
    vector<int> pos = findBitPosition(S[idxJSmallest-1]);

    vector<XY> results;
    results.push_back(points[0]);
    results.push_back(points[idxISmallest + 1]);

    for (size_t i = 0; i < pos.size(); i++)
    {
        results.push_back(points[pos[i] + 1]);
    }
    
    return results;
}
