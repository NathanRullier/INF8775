#include "allAlgo.h"

int base(vector<vector<int>> &value, vector<vector<int>> &cost)
{
    vector<vector<int>> profit(value.size(), vector<int>(value[0].size()));
    vector<vector<bool>> diggedUp(value.size(), vector<bool>(value[0].size(), false));

    for (int i = 0; i < value.size(); i++)
    {
        for (int j = 0; j < value[0].size(); j++)
        {
            profit[i][j] = value[i][j] - cost[i][j];
        }
    }

    int totalProfit = 0;
    int profitWithDig = 0;

    while (profitWithDig >= 0)
    {
        profitWithDig = -1;
        for (int i = 0; i < value.size() && profitWithDig <= 0; i++)
        {
            for (int j = 0; j < value[0].size() && profitWithDig <= 0; j++)
            {
                if (!diggedUp[i][j])
                {
                    profitWithDig = value_profit(j, i, profit, diggedUp, diggedUp);
                    if (profitWithDig > 0)
                    {
                        totalProfit += profitWithDig;
                    }
                }
            }
        }
    }

    return totalProfit;
}