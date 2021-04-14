#include "allAlgo.h"

int totalProfits(vector<vector<int>> &profit)
{
    vector<vector<bool>> diggedUp(profit.size(), vector<bool>(profit[0].size(), false));
    
    int profit_size = profit.size();

    int totalProfit = 0;
    bool continueWhile = true;
    while(continueWhile){
        vector<vector<int>> total_profits(profit.size(), vector<int>(profit[0].size()));
        int max_profit = -1;
        int max_profit_i = 0;
        int max_profit_j = 0;


        for (int i = 0; i < profit_size; i++)
        {
            for (int j = 0; j < profit_size; j++)
            {
                if (diggedUp[i][j] == false)
                {
                    total_profits[i][j] = profit[i][j];
                    if (i != 0)
                    {
                        int left = (j == 0) ? j : j - 1;
                        int right = (j == profit_size - 1) ? j : j + 1;
                        for (int z = left; z < right + 1; z++)
                        {

                            if (diggedUp[i][z] == false)
                            {
                                total_profits[i][j] += total_profits[i - 1][z];

                            }
                            
                        }
                    }
                    if (total_profits[i][j] > max_profit)
                    {
                        // cout << total_profits[i][j] << endl;
                        max_profit = total_profits[i][j];
                        max_profit_i = i;
                        max_profit_j = j;
                    }
                    // cout << max_profit << " " <<endl;
                }
            }
        }

        // for (int i = 0; i < profit.size(); i++)
        // {
        //     for (int j = 0; j < profit[0].size(); j++)
        //     {
        //         cout << total_profits[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        if( max_profit < 0){
            continueWhile = false;
            break;
        }
        int left = max_profit_j;
        int right = max_profit_j;
        int y = max_profit_i;
        // cout << y << endl;
        do
        {
            for (int i = left; i < right + 1; i++)
            {
                if (!diggedUp[y][i])
                {
                    diggedUp[y][i] = true;
                }
            }
            if (left != 0)
            {
                left--;
            }
            if (right != profit.size() - 1)
            {
                right++;
            }

            y--;
        } while (y >= 0);
    }

    for (int i = 0; i < profit_size; i++)
    {
        for (int j = 0; j < profit_size; j++)
        {
            if(diggedUp[i][j] == true){
                totalProfit += profit[i][j];
            }
        }
    }
    return totalProfit;
}