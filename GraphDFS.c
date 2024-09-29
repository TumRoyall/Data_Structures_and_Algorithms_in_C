#include <stdio.h>

#define MAX 1000

// data structure for the graph
int n, m; // n is number of vertices
// m is number of edges
int A[MAX][MAX]; // A[v] is the list of adjacent nodes of v
int sizeA[MAX];  // sizeA[v] is size of A[v]

// data structure for connected component
int ncc;      // is number of connected component of V
int icc[MAX]; // icc[u] is the index of connected component of u

void input()
{
    printf("Number of vertices is n = ");
    scanf("%d\n", &n);
    printf("Number of edges m = ");
    scanf("%d\n", &m);
    printf("The edges are: \n");
    for (int i = 1; i <= n; i++)
        sizeA[i] = 0; // set size = 0
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        A[v][sizeA[v]] = u;
        A[u][sizeA[u]] = v;
        sizeA[u]++;
        sizeA[v]++;
    }
}

void dfs(int u) // dfs of u
{
    icc[u] = ncc;
    for (int i = 0; i < sizeA[u]; i++)
    {
        int v = A[u][i];
        if (icc[v] == -1) // not visted
            dfs(v);
    }
}

void dfsGraph()
{
    for (int i = 1; i <= n; i++)
        icc[i] = -1; // set index of connect component = -1
    ncc = 0;
    for (int i = 1; i <= n; i++)
        if (icc[i] == -1)
        {
            ncc++;
            dfs(i);
        }
    for (int k = 1; k <= ncc; k++)
    {
        printf("Connected component %d: ", k);
        for (int v = 1; v <= n; v++)
            if (icc[v] == k)
                printf("%d ", v);
        printf("\n");
    }
}
void main()
{
    input();
    dfsGraph();
}