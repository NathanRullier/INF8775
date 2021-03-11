#include "allAlgo.h"
#include <math.h>
#include <limits>

vector<XY> glouton(vector<XY> & points)
{
    vector<XY> results;
    int numberOfPoints = points.size();
    
    results.push_back(points[0]);
    points.erase(points.begin());
    
    for(int z = 1; z < numberOfPoints; z++)
    {
        double smallestDistance = numeric_limits<double>::max();
        int indexSmallestDistancePoint = 0;
        for(int i = 0; i < points.size(); i++)
        {
            double presentDistance = sqrt(pow(results.back().x-points[i].x,2) + pow(results.back().y-points[i].y,2));
            if(presentDistance < smallestDistance)
            {
                smallestDistance = presentDistance;
                indexSmallestDistancePoint = i;
            }
        }
        
        results.push_back(points[indexSmallestDistancePoint]);
        points.erase(points.begin() + indexSmallestDistancePoint);
    }
    
    return results;
}