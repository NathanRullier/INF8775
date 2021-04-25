#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct
{
    int profit = 0;
    bool digged = false;
    int x;
    int y;
} cell;

void readFile(string const path, vector<vector<int>> &profit);
