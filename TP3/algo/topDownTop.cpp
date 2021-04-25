#include "allAlgo.h"

bool topDownTop(vector<vector<cell>> &cells)
{
    bool newDigged = false;

    vector<cell *> toDig{cells.size() * cells[0].size()};
    for (int i = 1; i < cells.size(); i++)
    {
        for (int j = 1; j < cells[0].size() - 1; j++)
        {
            cell *c = &cells[i][j];
            if (c->profit >= 0 && !c->digged)
            {
                toDig[0] = c;
                int position = 0;
                int tot = c->profit;
                int positive = 0;

                int from = j - 1;
                int to = j + 1;
                int newFrom = 0;
                int newTo = -1;
                for (int k = i - 1; k >= 0 && tot >= 0 && newFrom != -1; k--)
                {
                    newFrom = -1;
                    tot += positive;
                    positive = 0;
                    for (int l = from; l <= to && tot >= 0; l++)
                    {
                        if (!cells[k][l].digged)
                        {
                            toDig[++position] = &cells[k][l];
                            if (newFrom == -1)
                            {
                                newFrom = l - 1;
                            }
                            newTo = l + 1;
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
                    from = newFrom;
                    to = newTo;
                }
                if (tot >= 0)
                {
                    for (int k = position; k >= 0; k--)
                    {
                        newDigged = true;
                        toDig[k]->digged = true;
                        cout << toDig[k]->x << " " << toDig[k]->y << endl;
                    }
                }
            }
        }
    }

    return newDigged;
}
