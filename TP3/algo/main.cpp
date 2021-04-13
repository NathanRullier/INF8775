#include "allAlgo.h"
#include <time.h>
#include <cstring>

int main(int argc, char * argv[])
{
    clock_t start;
    clock_t end;
    
    std::vector<std::vector<int>> value;
    std::vector<std::vector<int>> cost;
    readFile("../data/N500_M500", value, cost);

    start = clock();

    std::vector<std::vector<int>> profit(value.size(),std::vector<int>(value[0].size()));
    std::vector<std::vector<bool>> diggedUp(value.size(),std::vector<bool>(value[0].size(), false));

    for(int i = 0; i < value.size(); i++){
        for(int j = 0; j < value[0].size(); j++){
            profit[i][j] = value[i][j] - cost[i][j];
            // cout << profit[i][j] << " ";
        }
        // cout <<endl;
    }
    // cout<<endl;

    bool whileBool = true;
    int totalProfit = 0;

    while(whileBool){
        int profitWithDig = -1;
        for(int i = 0; i < value.size(); i++){
            for(int j = 0; j < value[0].size(); j++){
                if(diggedUp[i][j] == false){
                    profitWithDig = value_profit(j,i,profit,diggedUp, diggedUp);
                    if(profitWithDig > 0){
                        // cout << i << " " << j <<endl;
                        totalProfit += profitWithDig;
                        break;
                    }
                    // if(i == value.size()-1 && j == value.size()-1 ){
                    //     whileBool = false;
                    //     break;
                    // }
                }
            }
            if(profitWithDig > 0){
                break;
            }
        }
        if(profitWithDig < 0){
            whileBool = false;
        }
    }

    end = clock();

    // for(int i = 0; i < value.size(); i++){
    //     for(int j = 0; j < value[0].size(); j++){
    //         cout << diggedUp[i][j];
    //     }
    //     cout <<endl;
    // }
    // cout << endl;

    cout << totalProfit << endl;

    double cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    cout << cpuTimeUsed << endl;

    return 0;
}