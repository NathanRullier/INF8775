#include "allAlgo.h"

int baseLookDown(vector<vector<int>> &profit)
{
    vector<int> sumProfit = profit.back();

    int totalProfit = 0;
    vector<vector<int8_t>> diggedUp(profit.size(), vector<int8_t>(profit[0].size(), 0));
    for (int i = 1; i < profit[0].size() - 2; i++)
    {
        if (profit[0][i] >= 0)
        {
            diggedUp[0][i] = 1;
            totalProfit += profit[0][i];
        }
        else
        {
            diggedUp[0][i] = -1;
        }
    }

    for (int i = 0; i < profit.size() - 1; i++)
    {
        for (int j = 1; j < profit[0].size() - 2; j++)
        {
            if(profit[i][j - 1] + profit[i][j] + profit[i][j + 1] > 1 && profit[i+1][j] >= 0){
                diggedUp[i+1][j] = 1;
                totalProfit += profit[i+1][j];
            }
        }
    }

    return totalProfit;
}
