#include "allAlgo.h"

int main(int argc, char * argv[])
{
    vector<XY> points = readFile("../data/N1000_0"); // argv[1]);
    vector<XY> result;

    switch ('0') // *argv[2])
    {
    case '0':
        result = glouton(points);
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

    if(true) // *argv[4] == '1')
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            cout << result[i].x << " " << result[i].y << endl;
        }
    }

    return 0;
}