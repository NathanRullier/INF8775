#include "allAlgo.h"
#include <utility>
#include <map>

typedef struct
{
    vector<pair<int, int>> parent = {};
    int profit;
    bool digged = false;
} cell;

bool checkParent(vector<pair<int, int>> &parent, vector<vector<cell>> &cells)
{
    for (pair<int, int> const &p : parent)
    {
        cell *c = &cells[p.first][p.second];
        if (!c->digged)
        {
            return false;
        }
        if (c->parent.size() > 0 && !checkParent(c->parent, cells))
        {
            return false;
        }
    }
    return true;
}

int baseLookDown2_0(vector<vector<int>> &profit)
{
    // init
    vector<vector<cell>> cells(profit.size(), vector<cell>(profit[0].size(), cell()));
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[0].size(); j++)
        {
            cells[i][j].profit = profit[i][j];
            if (j == 0 || j == cells[0].size() - 1 || (i == 0 && profit[i][j] >= 0))
            {
                cells[i][j].digged = true;
            }
            else if (i > 0)
            {
                cells[i][j].parent.push_back(pair<int, int>(i - 1, j - 1));
                cells[i][j].parent.push_back(pair<int, int>(i - 1, j));
                cells[i][j].parent.push_back(pair<int, int>(i - 1, j + 1));
            }
        }
    }

    // calculate if digged
    for (int i = 1; i < cells.size(); i++)
    {
        for (int j = 1; j < cells[0].size() - 1; j++)
        {
            cell *c = &cells[i][j];
            if (c->profit >= 0)
            {
                pair<int, int> p0 = cells[i][j].parent[0];
                cell *c0 = &cells[p0.first][p0.second];
                pair<int, int> p1 = cells[i][j].parent[1];
                cell *c1 = &cells[p1.first][p1.second];
                pair<int, int> p2 = cells[i][j].parent[2];
                cell *c2 = &cells[p2.first][p2.second];

                int neg = 0;
                if (c0->profit < 0)
                    neg -= c0->profit;
                if (c1->profit < 0)
                    neg -= c1->profit;
                if (c2->profit < 0)
                    neg -= c2->profit;

                if (c->profit >= neg) // (c0->profit + c1->profit + c2->profit + c->profit >= 0)
                {
                    c0->digged = true;
                    c1->digged = true;
                    c2->digged = true;
                    c->digged = true;
                }
            }
        }
    }

    for (int i = 1; i < cells.size(); i++)
    {
        for (int j = 1; j < cells[0].size() - 1; j++)
        {
            cell *c = &cells[i][j];
            if (c->profit >= 0)
            {
                pair<int, int> p0 = cells[i][j].parent[0];
                cell *c0 = &cells[p0.first][p0.second];
                pair<int, int> p1 = cells[i][j].parent[1];
                cell *c1 = &cells[p1.first][p1.second];
                pair<int, int> p2 = cells[i][j].parent[2];
                cell *c2 = &cells[p2.first][p2.second];

                if (c0->digged & c1->digged & c2->digged)
                {
                    c->digged = true;
                }
            }
        }
    }

    // select some not good
    vector<pair<int, int>> notSelected;
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 1; j < cells[0].size() - 1; j++)
        {
            if (!cells[i][j].digged)
            {
                notSelected.push_back(pair<int, int>(i, j));
            }
        }
    }

    for (int i = notSelected.size()-1; i >= 0; i--)
    {
        int tot = 0;
        for (int j = notSelected[i].first + 1; j < cells.size(); j++)
        {
            int tmp = j - notSelected[i].first;
            int from = notSelected[i].second - tmp;
            int to = notSelected[i].second + tmp;
            if (from < 1)
                from = 1;
            if (to > cells[0].size() - 2)
                to = cells[0].size() - 2;
            for (int k = from; k <= to; k++)
            {
                tot += cells[j][k].profit;
            }
        }
        if (tot >= -cells[notSelected[i].first][notSelected[i].second].profit)
        {
            cells[notSelected[i].first][notSelected[i].second].digged = true;
        }
        else
        {
            for (int j = notSelected[i].first; j < cells.size(); j++)
            {
                int tmp = j - notSelected[i].first;
                int from = notSelected[i].second - tmp;
                int to = notSelected[i].second + tmp;
                if (from < 1)
                    from = 1;
                if (to > cells[0].size() - 2)
                    to = cells[0].size() - 2;
                for (int k = from; k <= to; k++)
                {
                    cells[j][k].digged = false;
                }
            }
        }
    }

    int totalProfit = 0;
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 1; j < cells[0].size() - 1; j++)
        {
            if (cells[i][j].digged)
            {
                totalProfit += cells[i][j].profit;
            }
        }
    }

    // for (int i = 0; i < cells.size(); i++)
    // {
    //     for (int j = 0; j < cells[0].size(); j++)
    //     {
    //         cout << cells[i][j].digged << "";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    return totalProfit;
}
