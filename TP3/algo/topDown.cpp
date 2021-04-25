#include "allAlgo.h"

bool topDown(vector<vector<cell>> &cells)
{
    bool newDigged = false;

    for (int i = 1; i < cells.size(); i++)
    {
        for (int j = 1; j < cells[0].size() - 1; j++)
        {
            cell *c = &cells[i][j];
            if (c->profit < 0 && !c->digged && cells[i - 1][j - 1].digged && cells[i - 1][j].digged && cells[i - 1][j + 1].digged)
            {
                int tot = c->profit;
                int negative = 0;

                int from = j - 1;
                int to = j + 1;
                for (int k = i + 1; k < cells.size() && tot < 0; k++)
                {
                    tot += negative;
                    negative = 0;
                    for (int l = from; l <= to && tot < 0; l++)
                    {
                        if (cells[k][l].profit < 0)
                        {
                            negative += cells[k][l].profit;
                        }
                        else
                        {
                            tot += cells[k][l].profit;
                        }
                    }
                    from--;
                    if (from < 1)
                        from = 1;
                    to++;
                    if (to > cells.size() - 1)
                        to = cells.size() - 1;
                }
                if (tot >= 0)
                {
                    from = j;
                    to = j;
                    for (int k = i; k < cells.size(); k++)
                    {
                        for (int l = from; l <= to; l++)
                        {
                            if ((k != cells.size() - 1 || cells[k][l].profit >= 0) && cells[k - 1][l - 1].digged && cells[k - 1][l].digged && cells[k - 1][l + 1].digged)
                            {
                                newDigged = true;
                                cells[k][l].digged = true;
                                cout << cells[k][l].x << " " << cells[k][l].y << endl;
                            }
                        }
                        from--;
                        if (from < 1)
                            from = 1;
                        to++;
                        if (to > cells.size() - 1)
                            to = cells.size() - 1;
                    }
                }
            }
        }
    }

    return newDigged;
}
