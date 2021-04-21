#include "baseOps.h"

void readFile(string const path, vector<vector<int>> &profit)
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

                profit.resize(n, vector<int>(m));
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        myReadFile >> line;
                        profit[i][j] = stoi(line);
                    }
                }

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        myReadFile >> line;
                        profit[i][j] -= stoi(line);
                    }
                }
            }
        }
    }

    myReadFile.close();
}
