#include <stdio.h>
#include <limits.h>

#define MAX 1000

// Cấu trúc dữ liệu của graph
int n, m;        // n is number of vertices, m is number of edges
int A[MAX][MAX]; // Ma trận trọng số
int S;           // start node;

typedef struct Vertices
{
    int distance;
    int preNode;
    int visited;
} Vertices;

Vertices Node[MAX];

int findMinDistance() // Tìm khoảng cách ngắn nhất
{
    int NodeMin = -1;
    int min = INT_MAX;

    for (int i = 1; i <= n; i++)
    {
        if (min > Node[i].distance && Node[i].visited == 0)
        {
            NodeMin = i;
            min = Node[i].distance;
        }
    }

    return NodeMin;
}

void input()
{
    scanf("%d %d %d", &n, &m, &S);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            A[i][j] = 0;
        }
    }

    for (int i = 1; i <= m; i++)
    {
        int j, k, h; // h is distance of j and k 
        scanf("%d %d %d", &j, &k, &h);
        A[j][k] = h; // đồ thị vô hướng. (Undirected graph)
        A[k][j] = h;
    }
}


void printSolution()
{
    printf("Khoảng cách từ đỉnh bắt đầu đến các đỉnh khác:\n");
    for (int i = 1; i <= n; i++)
    {
        printf("Đỉnh %d: %d\n", i, Node[i].distance);
    }
}

void dijkstra(int start)
{
    for (int i = 1; i <= n; i++)
    {
        Node[i].distance = INT_MAX;
        Node[i].preNode = -1;
        Node[i].visited = 0;
    }

    Node[start].distance = 0;
    Node[start].preNode = start;

    while (1)
    {
        int u = findMinDistance();

        if (u == -1)
            break;

        Node[u].visited = 1;

        for (int i = 1; i <= n; i++)
        {
            if (Node[i].visited == 0 && A[u][i] != 0 && Node[u].distance + A[u][i] < Node[i].distance)
            {
                Node[i].distance = Node[u].distance + A[u][i];
                Node[i].preNode = u;
            }
        }
    }

    printSolution(Node);
}

int main()
{
    input();
    dijkstra(S);
    return 0;
}
