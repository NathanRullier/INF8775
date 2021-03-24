#include "allAlgo.h"
#include <time.h>

int main(int argc, char * argv[])
{
    vector<XY> points = readFile("../data/DP_N15_0"); // argv[1]);
    list<int> result;
    clock_t start;
    clock_t end;

    switch ('2') // *argv[2])
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
        start = clock();
        result = approximatif(points);
        end = clock();
        break;
    
    default:
        break;
    }

    if(false) // *argv[3] == '1')
    {
        double cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
        cout << cpuTimeUsed << endl;
    }

    if(true) // *argv[4] == '1')
    {
        for (int const& i : result) {
            cout << i << endl;
        }
    }

    return 0;
}