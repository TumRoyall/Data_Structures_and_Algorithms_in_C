#include <stdio.h>
#include <stdlib.h>

// Define cấu trúc của một cạnh trong đồ thị
typedef struct
{
    int src, dest, weight;
} Edge;

// Define cấu trúc của đồ thị
typedef struct
{
    int V, E;    // V là số đỉnh, E là số cạnh
    Edge *edges; // Danh sách các cạnh
} Graph;

// Define cấu trúc của một tập hợp con (disjoint set)
typedef struct
{
    int parent, rank; // parent là cha của tập hợp con, rank là chiều cao của tập hợp đó
} Subset;

// Tạo đồ thị mới với V đỉnh và E cạnh
Graph *createGraph(int V, int E)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge *)malloc(E * sizeof(Edge));
    return graph;
}

// Tìm tập hợp con gốc của một đỉnh i
int find(Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Hợp nhất hai tập hợp con chứa các đỉnh x và y
void Union(Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Hàm so sánh để sử dụng trong qsort để sắp xếp các cạnh theo trọng số tăng dần
int compare(const void *a, const void *b)
{
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

// Thuật toán Kruskal để tìm cây khung nhỏ nhất của đồ thị
void Kruskal(Graph *graph)
{
    int V = graph->V;
    Edge result[V - 1]; // danh sách các cạnh của cây khung nhỏ nhất
    int e = 0;          // Số cạnh đã thêm vào cây khung
    int i = 0;          // Biến đếm để duyệt qua các cạnh đã sắp xếp

    // Sắp xếp các cạnh theo trọng số tăng dần
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compare);

    // Tạo tập hợp con cho mỗi đỉnh
    Subset *subsets = (Subset *)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Duyệt qua từng cạnh
    while (e < V - 1 && i < graph->E)
    {
        Edge next_edge = graph->edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // Kiểm tra xem cạnh có tạo chu trình khi thêm vào cây khung không
        if (x != y)
        {
            result[e++] = next_edge; // Thêm cạnh vào cây khung
            Union(subsets, x, y);    // Hợp nhất tập hợp con của x và y
        }
    }

    // In ra các cạnh của cây khung nhỏ nhất
    printf("Edges in the Minimum Spanning Tree:\n");
    for (int j = 0; j < e; j++)
        printf("(%d, %d) -> %d\n", result[j].src, result[j].dest, result[j].weight);

    // Giải phóng bộ nhớ
    free(subsets);
}
// Hàm nhập đồ thị từ người dùng
void inputGraph(Graph *graph)
{
    printf("Enter the number of vertices: ");
    scanf("%d", &graph->V);
    printf("Enter the number of edges: ");
    scanf("%d", &graph->E);

    graph->edges = (Edge *)malloc(graph->E * sizeof(Edge));

    printf("Enter the edges (src dest weight):\n");
    for (int i = 0; i < graph->E; i++)
    {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }
}

int main()
{
    Graph *graph = createGraph(0, 0);

    // Nhập đồ thị từ người dùng
    inputGraph(graph);

    // Áp dụng thuật toán Kruskal và in kết quả
    Kruskal(graph);

    // Giải phóng bộ nhớ
    free(graph->edges);
    free(graph);

    return 0;
}