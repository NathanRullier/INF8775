#include "allAlgo.h"
#include <time.h>
#include <cstring>

int main(int argc, char * argv[])
{
    list<int> result;
    clock_t start;
    clock_t end;

    bool gotE = true;
    bool showTime = false;
    bool showPoints = false;
    bool showDist = false;

    string data = argv[1];
    string algo = argv[2];

    if(!strcmp(argv[1], ""))
    {
        gotE = false;
    }

    if(!strcmp(argv[3], "1"))
    {
        showTime = true;
    }

    if(!strcmp(argv[4], "1"))
    {
        showPoints = true;
    }

    if(!strcmp(argv[5], "1"))
    {
        showDist = true;
    }

    if(!gotE)
    {
        cout << "Vous devez entrer un chemin (-e CHEMIN_EXEMPLAIRE)\n";
        return 1;
    }

    vector<XY> points = readFile(data);

    if( "0" == algo){
        start = clock();
        result = glouton(points);
        end = clock();
    }
    else if("1" == algo){
        start = clock();
        result = dynamique(points);
        end = clock();
    }
    else if("2" == algo){
        start = clock();
        result = approximatif(points);
        end = clock();
    }

    if(showTime)
    {
        double cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
        cout << cpuTimeUsed << endl;
    }
    if(showPoints)
    {
        for (int const& i : result) {
            cout << i << endl;
        }
    }
    if(showDist)
    {
        float dist = 0;
        XY last = points[result.front()];
        bool first = true;
        for (int const& elm : result)
        {
            if(!first) 
            {
                dist += sqrt(pow(last.x-points[elm].x,2) + pow(last.y-points[elm].y,2));
            }
            else
            {
                first = false;
            }

            last = points[elm];
        }
        cout << dist << endl;
    }

    return 0;
}