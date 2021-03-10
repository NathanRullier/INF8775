#include "allAlgo.h"

int main(int argc, char * argv[])
{
    vector<XY> points = readFile(argv[1]);

    switch (*argv[2])
    {
    case '0':
        glouton(points);
        break;
    
    case '1':
        /* code */
        break;
    
    case '2':
        /* code */
        break;
    
    default:
        break;
    }

    return 0;
}