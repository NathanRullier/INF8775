#include "allAlgo.h"
#include <time.h>
#include <cstring>

int main(int argc, char *argv[])
{
    bool gotE = true;
    bool showTime = true;
    bool showProfit = true;

    string data = "../data/N10_M10"; // argv[1];
    string algo = "1";               // argv[2];

    // if(!strcmp(argv[1], ""))
    // {
    //     gotE = false;
    // }

    // if(!strcmp(argv[3], "1"))
    // {
    //     showTime = true;
    // }

    // if(!strcmp(argv[4], "1"))
    // {
    //     showProfit = true;
    // }

    // if(!gotE)
    // {
    //     cout << "Vous devez entrer un chemin (-e CHEMIN_EXEMPLAIRE)\n";
    //     return 1;
    // }

    vector<vector<int>> value;
    vector<vector<int>> cost;
    readFile(data, value, cost);

    vector<vector<int>> profits(value.size(), vector<int>(value[0].size(), 0));
    for (int i = 0; i < value.size(); i++)
    {
        for (int j = 0; j < value[0].size(); j++)
        {
            profits[i][j] = value[i][j] - cost[i][j];
        }
    }

    clock_t start;
    clock_t end;
    int profit = 0;

    if ("0" == algo)
    {
        start = clock();
        profit = base(profits);
        end = clock();
    }
    else if ("1" == algo)
    {
        start = clock();
        profit = dynamic(profits);
        end = clock();
    }

    if (showTime)
    {
        double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        cout << cpuTimeUsed << endl;
    }
    if (showProfit)
    {
        cout << profit << endl;
    }

    return 0;
}