#include "allAlgo.h"
#include <time.h>

int main(int argc, char * argv[])
{
    vector<XY> points = readFile("../data/DP_N10_0"); // argv[1]);
    vector<XY> result;
    clock_t start;
    clock_t end;

    switch ('1') // *argv[2])
    {
    case '0':
        start = clock();
        result = glouton(points);
        end = clock();
        break;
    
    case '1':
        start = clock();
        result = dynamique(points);
        end = clock();
        break;
    
    case '2':
        /* code */
        break;
    
    default:
        break;
    }

    if(false) // *argv[3] == '1')
    {
        double cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
        cout << cpuTimeUsed << endl;
    }

    if(false) // *argv[4] == '1')
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            cout << result[i].x << " " << result[i].y << endl;
        }
    }

    return 0;
}