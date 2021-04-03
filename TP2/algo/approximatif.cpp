#include "allAlgo.h"
#include <bits/stdc++.h>
list<int> approximatif(vector<XY> & points)
{
    list<int> results;
    int numberOfPoints = points.size();


    std::vector<std::vector<int>> graph(numberOfPoints,std::vector<int>(numberOfPoints));
	for(int i = 0; i < numberOfPoints; i++){
		for(int j = 0; j < numberOfPoints; j++){
			graph[i][j] = 0;
		}
	}
    
    for(int i = 0; i < numberOfPoints; i++){
		for(int j = 0; j < numberOfPoints; j++){
			graph[i][j] = graph[j][i] = sqrt(pow(points[j].x-points[i].x,2) + pow(points[j].y-points[i].y,2));
		}
	}

    int parent[numberOfPoints];
      
    int key[numberOfPoints]; 
      
    bool mstSet[numberOfPoints]; 
  
    for (int i = 0; i < numberOfPoints; i++){
        key[i] = INT_MAX;
        mstSet[i] = false; 
    }
  
    key[0] = 0; 
    parent[0] = -1;
  
    for (int count = 0; count < numberOfPoints - 1; count++)
    { 
        int min = INT_MAX;
        int min_index; 
  
        for (int v = 0; v < numberOfPoints; v++){
            if (mstSet[v] == false && key[v] < min){
                min = key[v];
                min_index = v;  
            }
        }
  
        mstSet[min_index] = true; 
  
        for (int v = 0; v < numberOfPoints; v++){
            if (graph[min_index][v] && mstSet[v] == false && graph[min_index][v] < key[v]) {
                parent[v] = min_index;
                key[v] = graph[min_index][v];
            }
            
        }
  
    }     

    int graphEulerian[(numberOfPoints-1)*2][2];
    
    for (int i = 1; i < numberOfPoints; i++){
        graphEulerian[i-1][0] = parent[i];
        graphEulerian[i-1][1] = i;
        graphEulerian[i+numberOfPoints-2][0] = i;
        graphEulerian[i+numberOfPoints-2][1] = parent[i];
    }
    

    bool used[(numberOfPoints-1)*2];
    for (int i = 0; i < (numberOfPoints-1)*2; i++){
        used[i] = false; 
    }

    vector<int> eulerianCycle;
    eulerianCycle.push_back(0);

    int z = 0;

    for (int i = 0; i < (numberOfPoints-1)*2 -1; i++){
        for (int j= 0; j < (numberOfPoints-1)*2; j++){
            if(!used[j] && graphEulerian[j][0] == eulerianCycle.back()){
                used[j] = true;
                eulerianCycle.push_back(graphEulerian[j][1]);
                break;
            }
        }
    }

    bool added[numberOfPoints];
    for (int i = 0; i < numberOfPoints; i++){
        added[i] = false; 
    }

    int a = 0;
    
    for (int i = 0; i < eulerianCycle.size(); i++){
        if(!added[eulerianCycle[i]]){
            
            results.push_back(eulerianCycle[i]);
            added[eulerianCycle[i]] = true;
            a++;
        }
    }
    
    results.push_back(results.front());

    graph.clear();
    eulerianCycle.clear();

    return results;
}