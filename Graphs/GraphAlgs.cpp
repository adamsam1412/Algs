#include <iostream>
#include <queue>

using std::endl;
using std::cout;
using std::queue;

#define V 4

struct graphV
{   
    int verts[V][V] = {{0, 1, 1, 0}, 
        {1, 0, 0, 0}, 
        {1, 0, 0, 0}, 
        {0, 0, 0, 0}}; 
};

struct Edge
{
    int source;
    int destination;
    int weight;
};
#pragma region Kruskal
struct graphE
{
    int v, E;
    Edge *edges;
};

graphE* createGraph(int verts, int edges)
{
    graphE* G = new graphE;
    G->v = verts;
    G->E = edges;
    G->edges = new Edge[edges];

    return G;
}

struct subset
{
    int parent;
    int rank;
};

int find(subset* sets, int x)
{
    if(sets[x].parent != x)
        sets[x].parent = find(sets, sets[x].parent);
    return sets[x].parent;
}

void Union(subset* sets, int x, int y)
{
    int xroot = find(sets, x);
    int yroot = find(sets, y);

    if(sets[xroot].rank < sets[yroot].rank)
        sets[xroot].parent = yroot;
    else if(sets[xroot].rank > sets[yroot].rank)
        sets[yroot].parent = xroot;
    else
    {
        sets[xroot].parent = yroot;
        sets[yroot].rank++;
    }
}

int comparer(const void *a, const void *b)
{
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;

    return a1->weight > b1->weight;
}






#pragma endregion Kruskal



struct Vertex
{
    int key;
    int neighbours[V];
};

struct graphA
{
    Vertex verts[V];
};


//BFS
// to implement disconnected graph case

bool isBipartite(graphV* G)
{
    int colors[V];
    for(auto i = 0; i < V; i++)
        colors[i] = -1;

    queue <int> Q;
    colors[0] = 1;
    Q.push(0);
        

    while(!Q.empty())
    {
        int x = Q.front();
        Q.pop();

        if(G->verts[x][x])
            return false;
        for(auto i = 0; i < V; ++i)
        {
            if(G->verts[x][i] && colors[i] == -1)
            {
                colors[i] = 1 - colors[x];
                Q.push(i);
            }

            else if(G->verts[x][i] && colors[x] == colors[i])
            {
                return false;
            }
        }

    }

    return true;    
}

void dfsVisit(graphV * G, bool* visited, int current)
{
    visited[current] = true;
    for(int i = 0; i < V; ++i)
    {
        if(!visited[i] && G->verts[current][i])
            dfsVisit(G, visited, i);
    }
}

int connectedComponents(graphV * G)
{
    bool visited[V];
    int count = 0;

    for(int i = 0; i < V; ++i)
        visited[i] = false;
    for(int i = 0; i < V; i++)
    {
        if(!visited[i])
        {
            count++;
            dfsVisit(G, visited, i);
        }
    }

    return count;    
}

bool isGraphCyclicDFS(graphV *G, int v, bool *visited, int parent)
{
    visited[v] = true;
    if(G->verts[v][v] == 1)
        return true;

    for(int u = 0; u < V; ++u)
    {
        
        cout << "u" << u << endl;
        if(!visited[u])
            if(G->verts[v][u] == 1 && isGraphCyclicDFS(G, u, visited, v))
                return true;
        else if(G->verts[v][u] && u != parent)
            return true;
    }
        
    return false;

}

bool isGraphCyclic(graphV *G)
{
    bool visited[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    for(int i = 0; i < V; ++i)
        if(!visited[i])
            if(isGraphCyclicDFS(G, i, visited, -1))
                return true;
    return false;
}

int graphDegree(graphV *G)
{
    int degree = 0;

    for(int i = 0; i < V; i++)
    {
        int vertexDegree = 0;
        for(int j = 0; j < V; j++)
            if(G->verts[i][j] == 1)
            {
                vertexDegree++;
                if(vertexDegree > degree)
                    degree = vertexDegree;
            }
    }
        

    return degree;
}


int MST(graphE *G)
{
    int mst = 0;
    int verts = G->v;
    Edge result[verts];

    int e = 0;
    int i = 0;

    qsort(G->edges, G->E, sizeof(G->edges[0]), comparer);

    subset *subsets = new subset[verts];

    for(int v = 0; v < verts; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while(e < verts - 1)
    {
        Edge nextEdge = G->edges[i++];
        
        int x = find(subsets, nextEdge.source);
        int y = find(subsets, nextEdge.destination);

        if(x != y)
        {
            result[e++] = nextEdge;
            Union(subsets, x, y);
            mst++;
        }
    }


    return mst;
}






int main()
{
    cout << "initialize graph" << endl;
    graphV* gVA = new graphV;

    graphE* graph = createGraph(V - 2, 3+1);

    graph->edges[0].source = 0;
    graph->edges[0].destination = 1;
    graph->edges[0].weight = 10;

    graph->edges[1].source = 1;
    graph->edges[1].destination = 0;
    graph->edges[1].weight = 20;

    graph->edges[2].source = 0;
    graph->edges[2].destination = 1;
    graph->edges[2].weight = 30;

    graph->edges[3].source = 1;
    graph->edges[3].destination = 0;
    graph->edges[3].weight = 30 + 10;



    cout << "MST: " << MST(graph) << endl;


    return 0;
}





























































