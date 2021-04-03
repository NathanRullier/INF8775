#include "allAlgo.h"
#include <algorithm>
#include <bitset> 

typedef struct node
{
    int val;
    float dist;
    XY * point;
    list<int> parents;
} node;

node calc(vector<XY> & points, node & parent);

list<int> dyn(vector<XY> & points)
{
    node root;
    root.val = 0;
    root.dist = 0;
    root.point = &points[0];
    root.parents.push_back(0);
    
    node result = calc(points, root);

    return result.parents;
}

node calc(vector<XY> & points, node & parent)
{
    vector<int> left;
    for(int i = 0; i < points.size(); i++)
    {
        if(parent.val != i)
        {
            bool ok = true;
            for(int const& parent: parent.parents)
            {
                if(parent == i){
                    ok = false;
                    break;
                }
            }
            if(ok)
            {
               left.push_back(i);
            }
        }
    }

    vector<node> nodes;
    if(left.size() == 0)
    {
        parent.dist += sqrt(pow(parent.point->x-points[0].x,2) + pow(parent.point->y-points[0].y, 2));
        parent.parents.push_back(0);
    }
    for(int const& l: left)
    {
        node nd;
        nd.val = l;
        nd.dist = parent.dist + sqrt(pow(parent.point->x-points[l].x,2) + pow(parent.point->y-points[l].y, 2));
        nd.point = &points[l];
        nd.parents = parent.parents; 
        nd.parents.push_back(l);

        nodes.push_back(calc(points, nd));
    }

    float minDist = -1;
    node minNode = parent;
    for(node const& nd: nodes)
    {
        if(minDist == -1 || minDist > nd.dist)
        {
            minDist = nd.dist;
            minNode = nd;
        }
    }

    return minNode;
}


