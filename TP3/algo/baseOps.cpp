    #include "baseOps.h"

void readFile(string const path, vector<vector<int>> &value, vector<vector<int>> &cost)
{
    ifstream myReadFile;
    string line;
    bool first = true;
    int n = 0;
    int m = 0;

    myReadFile.open(path);
    if (myReadFile.is_open())
    {
        for (int i = 0; i < 2; i++)
        {
            if (first)
            {
                first = false;

                myReadFile >> line;
                n = stoi(line);

                myReadFile >> line;
                m = stoi(line);

                value.resize(n, vector<int>(m));
                cost.resize(n, vector<int>(m));
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        myReadFile >> line;
                        value[i][j] = stoi(line);
                    }
                }

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        myReadFile >> line;
                        cost[i][j] = stoi(line);
                    }
                }
            }
        }
    }

    myReadFile.close();
}

int sumAll2D(vector<vector<int>> &profit)
{
    int sum = 0;

    for (vector<int> const &profitRow : profit)
    {
        for (int const &p : profitRow)
        {
            sum += p;
        }
    }

    return sum;
}

int value_profit(int x, int y, vector<vector<int>> &profit,
                 vector<vector<bool>> &diggedUp, vector<vector<bool>> diggedUpCopy)
{
    int total_profit = 0;
    int left = x;
    int right = x;

    do
    {
        for (int i = left; i < right + 1; i++)
        {
            if (!diggedUp[y][i])
            {
                total_profit += profit[y][i];
                diggedUpCopy[y][i] = true;
            }
        }
        if (left != 0)
        {
            left--;
        }
        if (right != profit.size() - 1)
        {
            right++;
        }

        y--;
    } while (y >= 0);

    if (total_profit > 0)
    {
        diggedUp = diggedUpCopy;
        // cout << x << " " << y2 << " " << total_profit << endl;
    }

    return total_profit;
    }

    std::vector<std::vector<int>> all_profit(std::vector<std::vector<int>> profit, std::vector<std::vector<bool>> &diggedUp)
    {

    std::vector<std::vector<int>> total_profits(profit.size(), std::vector<int>(profit[0].size()));
    int max_profit = 0;
    int max_profit_i = 0;
    int max_profit_j = 0;

    int profit_size = profit.size();

    for (int i = 0; i < profit_size; i++)
    {
        for (int j = 0; j < profit_size; j++)
        {
            if (diggedUp[i][j] == false)
            {

                total_profits[i][j] = profit[i][j];
                if (i != 0)
                {
                    int left = (j == 0) ? j : j - 1;
                    int right = (j == profit_size - 1) ? j : j + 1;
                    for (int z = left; z < right + 1; z++)
                    {

                        if (diggedUp[i][z] == false)
                        {
                            total_profits[i][j] += profit[i - 1][z];
                        
                            if (total_profits[i][j] > max_profit)
                            {
                                int max_profit = total_profits[i][j];
                                int max_profit_i = i;
                                int max_profit_j = j;
                            }
                        }
                    }
                }
            }
        }
    }
    return total_profits;
    }