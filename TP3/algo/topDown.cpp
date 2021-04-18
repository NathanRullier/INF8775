#include "allAlgo.h"

int sumToTop(cell *c, vector<vector<cell>> &cells, int profit = 0)
{
    int sum = c->profit + profit;
    int i = c->x;
    int j = c->y;
    bool ok = true;
    if (i > 0)
    {
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
        ok = cells[i - 1][j - 1].digged & cells[i - 1][j].digged & cells[i - 1][j + 1].digged;
    }

    c->digged = sum >= 0 && ok;

    return sum;
}

int topDown(vector<vector<int>> &profit)
{
#pragma region init

    vector<vector<cell>> cells(profit.size(), vector<cell>(profit[0].size(), cell()));
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[0].size(); j++)
        {
            cells[i][j].profit = profit[i][j];
            cells[i][j].x = i;
            cells[i][j].y = j;
            if (j == 0 || j == cells[0].size() - 1)
            {
                cells[i][j].digged = true;
            }
        }
    }

#pragma endregion init

#pragma region topDown

    vector<cell *> notSelect;
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 1; j < cells[0].size() - 1; j++)
        {
            cell *c = &cells[i][j];

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
                        if (to > cells[0].size()-1)
                            to = cells[0].size()-1;
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
            cell *c = notSelect[i];
            int curTot = sumToTop(c, cells);
            newTot += curTot >= 0 ? curTot : 0;
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
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[0].size(); j++)
        {
            cout << cells[i][j].digged << "";
        }
        cout << endl;
    }
    cout << endl;

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
