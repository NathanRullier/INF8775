#include "allAlgo.h"
#include <bits/stdc++.h>
list<int> approximatif(vector<XY> & points)
{
    list<int> results;
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

    cout<<"Edge \tWeight\n"; 
    for (int i = 1; i < numberOfPoints; i++){
        cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
    }

    int **graphEulerian = new int*[(numberOfPoints-1)*2];
    
    for (int i = 0; i < (numberOfPoints-1)*2; i++){
        graphEulerian[i]=new int[2];
    }
    
    for (int i = 1; i < numberOfPoints; i++){
        graphEulerian[i-1][0] = parent[i];
        graphEulerian[i-1][1] = i;
        graphEulerian[i+numberOfPoints-2][0] = i;
        graphEulerian[i+numberOfPoints-2][1] = parent[i];
    }

    bool used[(numberOfPoints-1)*2];
    for (int i = 0; i < (numberOfPoints-1)*2; i++){
        used[0] = false; 
    }

    vector<int> eulerianCycle;
    eulerianCycle.push_back(0);

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
        used[0] = false; 
    }
    
    for (int i = 0; i < eulerianCycle.size(); i++){
        if(!added[eulerianCycle[i]]){

            results.push_back(eulerianCycle[i]);
            added[eulerianCycle[i]] = true;
        }
    }
    results.push_back(results.front());

    return results;
}