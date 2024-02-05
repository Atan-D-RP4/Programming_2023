/*
    Implementation of:
    Graph Creation both Direccted and Undirected Using Edge inputs or Adjacency Matrix input.
    Graph Traversals Breadth First and Depth First
    Shortest Path between any Two Vertices Using Dijkstra's Algorithm
    Shortest Path between all Vertex pair Using Floyd-Warshall's Algorithm
 */

#include <stdio.h>
#include <stdlib.h>

#define INF 10000000

int **create_UDGraph(int vertices);
int **create_DGraph(int vertices);
void graphBFS(int **adj, int vertices, int start);
void graphDFS(int **adj, int vertices, int start);
void graphDFS_r(int **adj, int vertices, int start);
void graphDFSUtil(int **adj, int vertex, int *visited, int vertices);
void pathDijkstra(int **arr, int vertices, int src, int dst);
void printPath(int **pred, int i, int j);
int **getReachabilityMatrix(int **adj, int vertices);
void delete_matrix(int **arr, int size1, int size2);

int main()
{
    printf("No.of Vertices: ");
    int key, choice, **adj;
    scanf("%d", &key);

    printf("Select Input Type: \n");
    printf("1. Edges\n2. Adjacency Matrix\n[1/2]: ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            printf("Graph Type: \n");
            printf("1. Directed\n2. Undirected\n[1/2]: ");
            scanf("%d", &choice);
            adj = (choice == 1 ? create_DGraph(key) : create_UDGraph(key));
            break;
        case 2:
            printf("Enter %dx%d Adjacency Matrix: \n", key, key);
            adj = (int **) calloc(key, sizeof(int*));
            for (int i = 0; i < key; i++)
            {
                adj[i] = (int *) calloc(key, sizeof(int));
                for (int j = 0; j < key; j++)
                    scanf("%d", &adj[i][j]);
                printf("\n");
            }
    }

    printf("Adjacency Matrix of Given Graph:\n");
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
            printf("%3d ", adj[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("Breadth First Traversal: ");
    graphBFS(adj, key, 3);
    printf("Depth First Traversal: ");
    graphDFS(adj, key, 2);
    printf("\n");
    pathDijkstra(adj, key, 0, 7);

    int **reachabilityMatrix = getReachabilityMatrix(adj, key);
    printf("Reachability Matrix: \n");
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
            (reachabilityMatrix[i][j] != INF ? printf("%3d ", reachabilityMatrix[i][j]) : printf("INF "));
        printf("\n");
    }
    printf("\n");

    delete_matrix(adj, key, key);
    delete_matrix(reachabilityMatrix, key, key);
    return 0;
}

void graphDFSUtil(int **adj, int vertex, int *visited, int vertices)
{
    printf("%d ", vertex);
    visited[vertex] = 1;

    for (int i = 0; i < vertices; i++)
    {
        if (adj[vertex][i] && !visited[i])
        {
            graphDFSUtil(adj, i, visited, vertices);
        }
    }
}

void graphDFS_r(int **adj, int vertices, int start)
{
    int *visited = (int *) calloc(vertices, sizeof(int));

    graphDFSUtil(adj, start, visited, vertices);

    free(visited);
    printf("\n");
}

int **create_UDGraph(int vertices)
{
    printf("Enter Edges of an Undirected Graph\n");
    printf("Enter -1 and -1 to Exit\n");
    int src, dst, weight;
    int max_edges = ((vertices * (vertices - 1)) / 2);
    int **adj = (int **) calloc(vertices, sizeof(int *));
    for (int i = 0; i < vertices; i++)
        adj[i] = (int *) calloc(vertices, sizeof(int));
    for (int i = 0; i < max_edges; i++)
    {
        printf("Enter Source Vertex: ");
        scanf("%d", &src);
        printf("Enter Destination Vertex: ");
        scanf("%d", &dst);
        printf("Enter Weight of Edge: ");
        scanf("%d", &weight);
        if (src == -1 || dst == -1)
        {
            printf("All edges are given!\n");
            break;
        }
        else if (src < 0 || dst < 0 || src >= vertices || dst >= vertices || weight <= 0)
        {
            printf("Invalid\n");
            i--;
        }
        else
        {
            if (adj[src][dst] > 0)
            {
                i--;
                continue;
            }
            adj[src][dst] = weight;
            adj[dst][src] = weight;
        }
    }

    return adj;
}

int **create_DGraph(int vertices)
{
    printf("Enter Edges of an Directed Graph\n");
    printf("Enter -1 and -1 to Exit\n");
    int src, dst, weight; char str[100];
    int max_edges = (vertices * (vertices - 1));
    int **adj = (int **) calloc(vertices, sizeof(int *));
    for (int i = 0; i < vertices; i++)
        adj[i] = (int *) calloc(vertices, sizeof(int));
    for (int i = 0; i < max_edges; i++)
    {
        printf("Enter Source Vertex: ");
        scanf("%d", &src);
        printf("Enter Destination Vertex: ");
        scanf("%d", &dst);
        printf("Enter Weight of Edge: ");
        scanf("%d", &weight);
        if (src == -1 && dst == -1)
        {
            printf("All edges are given!\n");
            break;
        }
        else if (src < 0 || dst < 0 || src >= vertices || dst >= vertices || weight <= 0)
        {
            printf("Invalid\n");
            i--;
        }
        else
        {
            if (adj[src][dst] != 0)
            {
                i--;
                continue;
            }
            adj[src][dst] = weight;
        }
    }

    return adj;
}

void graphBFS(int **adj, int vertices, int start)
{
    int visited[vertices];
    int queue[vertices], front = 0, rear = 0;

    for (int i = 0; i < vertices; i++)
        visited[i] = 0;

    visited[start] = 1;

    queue[rear++] = start;
    while (front < rear)
    {
        start = queue[front++];
        printf("%2d ", start);
        for (int i = 0; i < vertices; i++)
        {
            if (adj[start][i] && !visited[i])
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void graphDFS(int **adj, int vertices, int start)
{
    int stack[vertices], top = -1;
    int visited[vertices];

    for (int i = 0; i < vertices; i++)
    {
        stack[i] = 0;
        visited[i] = 0;
    }

    stack[++top] = start;
    visited[start] = 1;

    while (top != -1)
    {
        int vertex = stack[top--];
        printf("%2d ", vertex);

        for (int i = 0; i < vertices; i++)
        {
            if (adj[vertex][i] && !visited[i])
            {
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void pathDijkstra(int **arr, int vertices, int src, int dst)
{
    int distance[vertices], visited[vertices];

    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
    }

    distance[src] = 0;

    for (int count = 0; count < vertices - 1; count++)
    {
        int minDistance = INF, minIndex = -1;

        for (int v = 0; v < vertices; v++)
        {
            if (!visited[v] && distance[v] < minDistance)
            {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        // All remaining vertices are unreachable
        if (minIndex == -1)
            break;

        visited[minIndex] = 1;

        for (int v = 0; v < vertices; v++)
        {
            if ((!visited[v] && arr[minIndex][v] && distance[minIndex] != INF) &&
                (distance[minIndex] + arr[minIndex][v] < distance[v]))
            {
                distance[v] = distance[minIndex] + arr[minIndex][v];
            }
        }
    }

    if (distance[dst] == INF)
    {
        printf("There is no path from %d to %d\n", src, dst);
    }
    else
    {
        printf("Shortest path from %d to %d: %d\n", src, dst, distance[dst]);
    }
    printf("\n");
}

void printPath(int **pred, int i, int j)
{
    if (i == j)
    {
        printf("%d ", i);
    }
    else if (pred[i][j] == -1)
    {
        printf("No path from %d to %d exists", i, j);
    }
    else
    {
        printPath(pred, i, pred[i][j]);
        printf("%d ", j);
    }
}

int **getReachabilityMatrix(int **adj, int vertices)
{
    int **reachabilityMatrix = (int **) calloc(vertices, sizeof(int *));
    int **pred = (int **)calloc(vertices, sizeof(int *));
    for (int i = 0; i < vertices; i++)
    {
        reachabilityMatrix[i] = (int *) calloc(vertices, sizeof(int));
        pred[i] = (int *)calloc(vertices, sizeof(int));
        for (int j = 0; j < vertices; j++)
        {
            reachabilityMatrix[i][j] = (adj[i][j] != 0 ? adj[i][j] : INF);
            pred[i][j] = (i == j || adj[i][j] == 0 ? -1 : i);
        }
    }
    // Floyd-Warshall's Algorithm
    for (int k = 0; k < vertices; k++)
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (reachabilityMatrix[i][k] != INF && reachabilityMatrix[k][j] != INF &&
                    reachabilityMatrix[i][k] + reachabilityMatrix[k][j] < reachabilityMatrix[i][j])
                {
                    reachabilityMatrix[i][j] = reachabilityMatrix[i][k] + reachabilityMatrix[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }

    printf("Shortest Paths Matrix:\n");

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (i != j)
            {
                printf("Shortest path from %d to %d: ", i, j);
                printPath(pred, i, j);
                printf("\n");
            }
        }
            printf("\n");
    }

    return reachabilityMatrix;
}

void delete_matrix(int **arr, int size1, int size2)
{
    for (int i = 0; i < size1; i++)
        free(arr[i]);
    free(arr);
}
