#include "allAlgo.h"
#include <time.h>
#include <cstring>

int main(int argc, char *argv[])
{
    bool gotE = true;
    bool showTime = false;
    bool showProfit = false;
    bool showDigged = false;
    bool showPoints = false;

    string data = "../data/" + (string)argv[1];

    if (!strcmp(argv[2], "1"))
    {
        showPoints = true;
    }

    if (!strcmp(argv[3], "1"))
    {
        showTime = true;
    }

    if (!strcmp(argv[4], "1"))
    {
        showProfit = true;
    }

    if (!strcmp(argv[5], "1"))
    {
        showDigged = true;
    }

    vector<vector<int>> profits;
    readFile(data, profits);

    clock_t start = clock();
    vector<vector<cell>> profit_c = topDownTop(profits);
    clock_t end = clock();

    if (showDigged)
    {
        for (int i = 0; i < profit_c.size(); i++)
        {
            for (int j = 0; j < profit_c[0].size(); j++)
            {
                cout << profit_c[i][j].digged << "";
            }
            cout << endl;
        }
        cout << endl;
    }
    if (showPoints)
    {
        for (int i = 1; i < profit_c.size(); i++)
        {
            for (int j = 1; j < profit_c[0].size() - 1; j++)
            {
                if (profit_c[i][j].digged)
                {
                    cout << i - 1 << " " << j - 1 << endl;
                }
            }
        }
    }
    if (showTime)
    {
        double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        cout << cpuTimeUsed << endl;
    }
    if (showProfit)
    {

        int profit = 0;
        for (int i = 1; i < profit_c.size(); i++)
        {
            for (int j = 1; j < profit_c[0].size() - 1; j++)
            {
                if (profit_c[i][j].digged)
                {
                    profit += profit_c[i][j].profit;
                }
            }
        }
        cout << profit << endl;
    }

    return 0;
}