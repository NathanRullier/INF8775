#include "allAlgo.h"

int base(vector<vector<int>> &profit)
{
    vector<vector<bool>> diggedUp(profit.size(), vector<bool>(profit[0].size(), false));

    int totalProfit = 0;
    int profitWithDig = 0;

    while (profitWithDig >= 0)
    {
        profitWithDig = -1;
        for (int i = 0; i < profit.size() && profitWithDig <= 0; i++)
        {
            for (int j = 0; j < profit[0].size() && profitWithDig <= 0; j++)
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