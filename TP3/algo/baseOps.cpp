#include "baseOps.h"

int readFile(string const path, std::vector<std::vector<int>>& value,std::vector<std::vector<int>>& cost)
{
    int n = 0;
    int m = 0;
    ifstream myReadFile;
    string line;
    bool first = true;

    myReadFile.open(path);
    if (myReadFile.is_open()) {
        for(int z = 0; z < 2; z++){
            if(!first)
            {
                std::vector<std::vector<int>> valueRead(n,std::vector<int>(m));
                std::vector<std::vector<int>> costRead(n,std::vector<int>(m));

                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        myReadFile >> line;
                        valueRead[i][j] = stoi(line);
                    }
                }
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        myReadFile >> line;
                        costRead[i][j] = stoi(line);
                    }
                }
                value = valueRead;
                cost = costRead;
            }
            if(first){
                first = false;
                myReadFile >> line;
                n = stoi(line);
                myReadFile >> line;
                m = stoi(line);
            }
        }
    }
    
    myReadFile.close();

    return 0;
}