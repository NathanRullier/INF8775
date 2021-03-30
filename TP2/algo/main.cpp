#include "allAlgo.h"
#include <time.h>
#include <cstring>

int main(int argc, char * argv[])
{
    list<int> result;
    clock_t start;
    clock_t end;

    bool gotE = false;
    bool gotA = false;
    bool showTime = false;
    bool showPoints = false;

    string data = "";
    string algo = "";

    for(int i = 0; i< argc; i++){

        if(!strcmp(argv[i], "-a")){
                gotA = true;
                algo = argv[++i];
        }
        else if(!strcmp(argv[i], "-e"))
        {
            gotE = true;
            data = argv[++i];
        }
        else if(!strcmp(argv[i], "-t"))
        {
            showTime = true;
        }
        else if(!strcmp(argv[i], "-p"))
        {
            showPoints = true;
        }
    }

    if(!gotE)
    {
        cout << "Vous devez entrer un chemin (-e CHEMIN_EXEMPLAIRE)\n";
        return 1;
    }
    if(!gotA)
    {
        cout << "Vous devez entrer un type d'algorithme (-a {brute, recursif, seuil})\n";
        return 1;
    }

    vector<XY> points = readFile(data);

    if( "glouton" == algo){
        start = clock();
        result = glouton(points);
        end = clock();
    }
    else if("progdyn" == algo){
        start = clock();
        result = dynamique(points);
        end = clock();
    }
    else if("approx" == algo){
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

    return 0;
}