#include "baseOps.h"

vector<XY> readFile(string const path)
{
    ifstream myReadFile;
    string line;
    vector<XY> point;
    bool first = true;

    myReadFile.open(path);
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> line;
            if(!first) 
            {
                XY xy;
                xy.x = stoi(line);
                myReadFile >> line;
                xy.y = stoi(line);

                point.push_back(xy);
            }
            first = false;
        }
    }
    
    myReadFile.close();  

    point.pop_back();
      
    return point;
}