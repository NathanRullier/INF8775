#include "allAlgo.h"

int baseLookDown(vector<vector<int>> &profit)
{
    int totalProfit = 0;
    vector<vector<int>> diggedUp(profit.size(), vector<int>(profit[0].size(), 0));
    for (int i = 1; i < profit[0].size() - 1; i++)
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
        for (int j = 1; j < profit[0].size() - 1; j++)
        {
            if (diggedUp[i][j - 1] + diggedUp[i][j] + diggedUp[i][j + 1] > 1 && profit[i + 1][j] >= 0)
            {
                diggedUp[i + 1][j] = 1;
                totalProfit += profit[i + 1][j];
            }
            else{
                diggedUp[i + 1][j] = -1;
            }
        }
    }
    for (int i = 0; i < diggedUp.size(); i++)
    {
        for (int j = 0; j < diggedUp[0].size(); j++)
        {
            cout << diggedUp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return totalProfit;
}
