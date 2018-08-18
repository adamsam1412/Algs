//To section all these algorithms off
#include <iostream>
#include <queue>
#include <list>

#define V 6
#define E 10
using namespace std;

struct G{
    int head[V+1];
    int next[2E];
};

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

int connectedComponents(G& graph)
{
    int colors[V];
    
    for(auto i = 0; i < V; ++i)
        colors[i] = -1;

    int count = 0;
    for(auto i = 0; i < V; ++i)
    {
        if(colors[i] == -1)
        {
            count++;

        }
    }

}

void dfsVisit(G & graph, int colors[], int current)
{
    colors[current] = 1;
    for(auto i = graph.head[current]; i < graph.head[current+1]; ++i)
    {
        if(colors[graph.next[i]] == -1)
            dfsVisit(graph, colors, graph.next[i]);
    }
}



