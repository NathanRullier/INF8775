#include "allAlgo.h"
#include <time.h>
#include <cstring>

vector<vector<cell>> initCells(vector<vector<int>> profit)
{
    vector<vector<cell>> cells(profit.size() + 1, vector<cell>(profit[0].size() + 2, cell()));
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[0].size(); j++)
        {
            bool isDigged = (i == 0 || j == 0 || j == cells[0].size() - 1);
            cells[i][j].digged = isDigged;
            cells[i][j].x = i - 1;
            cells[i][j].y = j - 1;
            if (i > 0 && j > 0 && j < cells[0].size() - 1)
            {
                cells[i][j].profit = profit[i - 1][j - 1];
            }
        }
    }
    return cells;
}

int main(int argc, char *argv[])
{
    string data = (string)argv[1];

    vector<vector<int>> profits;
    readFile(data, profits);

    clock_t start = clock();
    vector<vector<cell>> profit_c = initCells(profits);
    bool newDigged = true;
    while (newDigged)
    {
        newDigged = topDownTop(profit_c);
        if (newDigged)
        {
            newDigged = topDown(profit_c);
        }
    }
    clock_t end = clock();

    return 0;
}