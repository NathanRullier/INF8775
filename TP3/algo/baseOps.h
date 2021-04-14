#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readFile(string const path, vector<vector<int>> &value, vector<vector<int>> &cost);

int sumAll2D(vector<vector<int>> &profit);

int value_profit(int x, int y, vector<vector<int>> &profit, vector<vector<bool>> &diggedUp, vector<vector<bool>> diggedUpCopy);

std::vector<std::vector<int>> all_profit(std::vector<std::vector<int>> profit, std::vector<std::vector<bool>> & diggedUp);
