#include "allAlgo.h"

vector<vector<cell>> topDownTop(vector<vector<int>> &profit)
{
#pragma region init

    vector<vector<cell>> cells(profit.size() + 1, vector<cell>(profit[0].size() + 2, cell()));
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[0].size(); j++)
        {
            bool isDigged = (i == 0 || j == 0 || j == cells[0].size() - 1);
            cells[i][j].digged = isDigged;
            if (i > 0)
            {
                cells[i][j].profit = profit[i - 1][j];
            }
        }
    }

#pragma endregion init

#pragma region topDownTop

    for (int i = 1; i < cells.size(); i++)
    {
        for (int j = 1; j < cells[0].size() - 1; j++)
        {
            cell *c = &cells[i][j];
            if (c->profit >= 0 && !c->digged)
            {
                int tot = c->profit;
                bool isNotAllDigged = true;
                int positive = 0;
                for (int k = i - 1; k >= 0 && tot >= 0 && isNotAllDigged; k--)
                {
                    isNotAllDigged = false;
                    tot += positive;
                    positive = 0;

                    int from = j - (i - k);
                    int to = j + (i - k);
                    if (from < 1)
                        from = 1;
                    if (to > cells[0].size() - 1)
                        to = cells[0].size() - 1;

                    for (int l = from; l <= to && tot >= 0; l++)
                    {
                        isNotAllDigged |= !cells[k][l].digged;
                        if (!cells[k][l].digged)
                        {
                            if (cells[k][l].profit >= 0)
                            {
                                positive += cells[k][l].profit;
                            }
                            else
                            {
                                tot += cells[k][l].profit;
                            }
                        }
                    }
                }
                if (tot >= 0)
                {
                    isNotAllDigged = true;
                    for (int k = i; k >= 0 && isNotAllDigged; k--)
                    {
                        isNotAllDigged = false;

                        int from = j - (i - k);
                        int to = j + (i - k);
                        if (from < 1)
                            from = 1;
                        if (to > cells[0].size() - 1)
                            to = cells[0].size() - 1;

                        for (int l = from; l <= to; l++)
                        {
                            isNotAllDigged |= !cells[k][l].digged;
                            if (!cells[k][l].digged)
                            {
                                cells[k][l].digged = true;
                            }
                        }
                    }
                }
            }
        }
    }

#pragma endregion topDownTop

#pragma region showInfo
    // for (int i = 0; i < cells.size(); i++)
    // {
    //     for (int j = 0; j < cells[0].size(); j++)
    //     {
    //         cout << cells[i][j].profit << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
#pragma endregion showInfo

    return cells;
}
