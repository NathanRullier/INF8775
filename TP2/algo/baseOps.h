#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct
{
    int x;
    int y;
} XY;

vector<XY> readFile(string const path);
