#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Edge
{
    int source, destination, weight;

};

struct Graph
{
    int V, E;
    Edge *edge;
};

struct subset
{
    int parent;
    int rank;
};


Graph * createGraph(int V, int E)
{
    Graph * graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];

    return graph;
}

int find(subset subsets[], int i)
{
    if(subsets[i].parent != i)
        find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    if(subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if(subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int KruskalMSTDepth(Graph* graph)
{
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;

    //quickSort(graph->edge);

    subset* subsets = new subset[V];

    for(int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while(e < V - 1)
    {
        Edge nextEdge = graph->edge[i++];

        int x = find(subsets, nextEdge.source);
        int y = find(subsets, nextEdge.destination);

        if(x != y)
        {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
        //discarding edge as it makes cycle or is duplicated one

    }

    return subsets[find(subsets, result[0].source)].rank;
}
