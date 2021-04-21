#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct
{
    int profit;
    bool digged = false;
} cell;

void readFile(string const path, vector<vector<int>> &profit);
