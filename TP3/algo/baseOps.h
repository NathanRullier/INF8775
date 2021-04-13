#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int readFile(string const path, std::vector<std::vector<int>>& value,std::vector<std::vector<int>>& cost);

int value_profit(int x, int y,std::vector<std::vector<int>> profit, std::vector<std::vector<bool>> & diggedUp, std::vector<std::vector<bool>> diggedUpCopy);