#include "allAlgo.h"

typedef struct
{
    int profit;
    bool digged = false;
    int i = 0;
    int j = 0;
} cell_td;

int sumToTop(cell_td *cell, vector<vector<cell_td>> &cells, int profit = 0)
{
    int sum = cell->profit + profit;
    int i = cell->i;
    int j = cell->j;
    
    if (!cells[i - 1][j - 1].digged)
    {
        sum = sumToTop(&cells[i - 1][j - 1], cells, sum);
    }
    if (!cells[i - 1][j].digged)
    {
        sum = sumToTop(&cells[i - 1][j], cells, sum);
    }
    if (!cells[i - 1][j + 1].digged)
    {
        sum = sumToTop(&cells[i - 1][j + 1], cells, sum);
    }

    cell->digged = sum >= 0;

    return sum;
}

int topDown(vector<vector<int>> &profit)
{
#pragma region init

    vector<vector<cell_td>> cells(profit.size(), vector<cell_td>(profit[0].size(), cell_td()));
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[0].size(); j++)
        {
            cells[i][j].profit = profit[i][j];
            cells[i][j].i = i;
            cells[i][j].j = j;
            if (j == 0 || j == cells[0].size() - 1)
            {
                cells[i][j].digged = true;
            }
        }
    }

#pragma endregion init

#pragma region topDown

    vector<cell_td *> notSelect;
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 1; j < cells[0].size() - 1; j++)
        {
            cell_td *c = &cells[i][j];

            if (i == 0 || cells[i - 1][j - 1].digged & cells[i - 1][j].digged & cells[i - 1][j + 1].digged)
            {
                if (c->profit >= 0)
                {
                    c->digged = true;
                }
                else
                {
                    int tot = -c->profit;
                    for (int k = i + 1; k < cells.size() && tot > 0; k++)
                    {
                        int from = j - (k - i);
                        int to = j + (k - i);
                        if (from < 1)
                            from = 1;
                        if (to > cells[0].size())
                            to = cells[0].size();
                        for (int l = from; l <= to && tot > 0; l++)
                        {
                            tot -= cells[k][l].profit;
                        }
                    }

                    c->digged = tot <= 0;
                }
            }
            else
            {
                c->digged = false;
            }
            if (!c->digged && c->profit >= 0)
            {
                notSelect.push_back(c);
            }
        }
    }

#pragma endregion topDown

#pragma region validateNotDigged

    int oldTot = -1;
    int newTot = 0;
    while (oldTot < newTot)
    {
        oldTot = newTot;
        newTot = 0;
        for (int i = notSelect.size() - 1; i >= 0; i--)
        {
            cell_td *c = notSelect[i];
            newTot += sumToTop(c, cells);
        }
    }

#pragma endregion validateNotDigged

#pragma region calculateProfit

    int totalProfit = 0;
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[0].size(); j++)
        {
            if (cells[i][j].digged)
            {
                totalProfit += cells[i][j].profit;
            }
        }
    }

#pragma endregion calculateProfit

#pragma region showInfo
    // for (int i = 0; i < cells.size(); i++)
    // {
    //     for (int j = 0; j < cells[0].size(); j++)
    //     {
    //         cout << cells[i][j].digged << "";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

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

    return totalProfit;
}
