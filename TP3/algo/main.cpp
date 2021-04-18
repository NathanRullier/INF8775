#include "allAlgo.h"
#include <time.h>
#include <cstring>

int main(int argc, char *argv[])
{
    bool gotE = true;
    bool showTime = true;
    bool showProfit = true;
    bool showDigged = false;

    string data = "../data/" + (string)argv[1]; //N200_M300"; // argv[1];
    string algo = argv[2];

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

    clock_t start;
    clock_t end;
    int profit = 0;
    vector<vector<cell>> profit_c;

    if ("0" == algo)
    {
        start = clock();
        profit = base(profits);
        end = clock();
    }
    else if ("1" == algo)
    {
        start = clock();
        profit = totalProfits(profits);
        end = clock();
    }
    else if ("2" == algo)
    {
        start = clock();
        profit_c = topDownTop(profits);
        end = clock();
    }
    else if ("3" == algo)
    {
        start = clock();
        profit_c = topDown(profits);
        end = clock();
    }

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
    if (showTime)
    {
        double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        cout << cpuTimeUsed << endl;
    }
    if (showProfit)
    {
        if (profit_c.size() > 0)
        {
            profit = 0;
        }
        for (int i = 1; i < profit_c.size(); i++)
        {
            for (int j = 0; j < profit_c[0].size(); j++)
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