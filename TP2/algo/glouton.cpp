#include "allAlgo.h"

list<int> glouton(vector<XY> points)
{
    list<int> ordre = {0};
    vector<int> num;
    for (int i = 1; i < points.size(); i++)
    {
        num.push_back(i);
    }
    int numberOfPoints = points.size();
    
    XY last = points[0];
    points.erase(points.begin());
    
    for(int z = 1; z < numberOfPoints; z++)
    {
        double smallestDistance = numeric_limits<double>::max();
        int indexSmallestDistancePoint = 0;
        for(int i = 0; i < points.size(); i++)
        {
            double presentDistance = sqrt(pow(last.x-points[i].x,2) + pow(last.y-points[i].y,2));
            if(presentDistance < smallestDistance)
            {
                smallestDistance = presentDistance;
                indexSmallestDistancePoint = i;
            }
        }
        
        last = points[indexSmallestDistancePoint];
        ordre.push_back(num[indexSmallestDistancePoint]);
        points.erase(points.begin() + indexSmallestDistancePoint);
        num.erase(num.begin() + indexSmallestDistancePoint);
    }

    ordre.push_back(0);
    
    return ordre;
}