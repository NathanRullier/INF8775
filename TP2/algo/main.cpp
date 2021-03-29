#include "allAlgo.h"
#include <time.h>
#include <cstring>

int main(int argc, char * argv[])
{
    vector<XY> points = readFile(argv[1]); // argv[1]);
    list<int> result;
    clock_t start;
    clock_t end;

    if(!strcmp("glouton" , argv[2])){
        start = clock();
        result = glouton(points);
        end = clock();
    }
    
    else if(!strcmp("progdyn",argv[2])){
        start = clock();
        result = dynamique(points);
        end = clock();
    }
    else if(!strcmp("approx",argv[2])){
        start = clock();
        result = approximatif(points);
        end = clock();
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