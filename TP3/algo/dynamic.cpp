#include "allAlgo.h"

int dynamic(vector<vector<int>> &profit)
{
    vector<int> sumProfit = profit.back();
    vector<vector<bool>> diggedUp(profit.size(), vector<bool>(profit[0].size(), false));
    for (int i = 0; i < diggedUp[0].size(); i++)
    {
        diggedUp[diggedUp.size()-1][0] = true;
    }
    

    for (int i = profit.size() - 2; i >= 0; i--)
    {
        for (int j = 1; j < profit.size() - 1; j++)
        {
            sumProfit[j] += profit[i][j - 1] + profit[i][j] + profit[i][j + 1];
            diggedUp[i][j] = true;
        }
    }

    int totalProfit = 0;
    for (int const &p : sumProfit)
    {
        if (p > 0)
        {
            totalProfit += p;
        }
    }

    return totalProfit;
}
