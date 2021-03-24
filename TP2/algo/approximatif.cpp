#include "allAlgo.h"

list<int> approximatif(vector<XY> & points)
{
    vector<XY> results;
    int numberOfPoints = points.size();

    int **graph = new int*[numberOfPoints];
	for(int i = 0; i < numberOfPoints; i++){
		graph[i] = new int[numberOfPoints];
		for(int j = 0; j < numberOfPoints; j++){
			graph[i][j] = 0;
		}
	}
    
    for(int i = 0; i < numberOfPoints; i++){
		for(int j = 0; j < numberOfPoints; j++){
			graph[i][j] = graph[j][i] = sqrt(pow(results.back().x-points[i].x,2) + pow(results.back().y-points[i].y,2));
		}
	}
    
    results.push_back(points[0]);
    points.erase(points.begin());

    return results;
}