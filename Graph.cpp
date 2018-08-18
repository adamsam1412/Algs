#include <iostream>
#include <queue>

#define V 6

using namespace std;

bool isBipartite(int G[][V], int src)
{
    int color[V];
    for(int i = 0; i < V; i++)
        color[V] = -1;
    color[src] = 1;

    queue<int> q;
    q.push(src);

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        if(G[u][u] == 1)
            return false;
        
        for(int v = 0; v < V; ++v)
        {
            if(G[u][v] && color[v] == -1)
            {
                color[v] = 1 - color[u];
                q.push(v);
            }

            else if(G[u][v] && color[v] == color[u])
                return false;
        }
    }
    return true;
}


