#include <stdio.h>

#define N 1000

// Data Structure for the queue
int q[N];
int head = -1, tail = -1;

// data structure for the graph
int n, m;    // number of nodes and edges
int A[N][N]; // A[v] is the list of adjacent nodes to v
int szA[N];  // szA[v] is the size of A[v]

// data structure for BFS connected component
int ncc;    // number of connected component
int icc[N]; // icc[v] is the index of connected component of v
int d[N];   // d[v] is the distance from the starting node to v in the BFS tree

void initQueue()
{
    head = -1, tail = -1;
}

void pushQ(int v)
{
    tail++;
    q[tail] = v;
    if (head == -1)
        head = tail;
}

int popQ()
{
    if (head == -1)
        return -1; // queue empty
    int v = q[head];
    if (head == tail)
    {
        head = -1;
        tail = -1;
    }
    else
        head++;
    return v;
}
int empty()
{
    return head == -1 && tail == -1;
}

void input()
{
    scanf("%d%d", &n, &m);
    for (int v = 1; v <= n; v++)
        szA[v] = 0;
    for (int k = 1; k <= m; k++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        A[v][szA[v]] = u;
        A[u][szA[u]] = v;
        szA[v]++;
        szA[u]++;
    }
}

void bfs(int u)
{
    initQueue();
    icc[u] = ncc;
    pushQ(u);
    d[u] = 0;
    while (!empty())
    {
        int v = popQ();
        for (int i = 0; i < szA[v]; i++)
        {
            int x = A[v][i];
            if (d[x] == -1)
            {
                d[x] = d[v] + 1;
                pushQ(x);
                icc[x] = ncc;
            }
        }
    }
}
void bfsGraph()
{
    for (int v = 1; v <= n; v++)
        d[v] = -1;
    ncc = 0;
    for (int v = 1; v <= n; v++)
        if (d[v] == -1) // check visited
        {
            ncc++;
            bfs(v);
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
    bfsGraph();
}