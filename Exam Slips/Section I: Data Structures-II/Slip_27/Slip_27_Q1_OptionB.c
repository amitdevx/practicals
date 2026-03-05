/* Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency
   matrix. Implement function to traverse the graph using Breadth First Search (BFS) traversal. */

#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];

void BFS(int vertices, int start) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    int vertex, i;

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS Traversal starting from vertex %d: ", start);
    while (front < rear) {
        vertex = queue[front++];
        printf("%d ", vertex);
        for (i = 0; i < vertices; i++) {
            if (adj[vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

int main() {
    int vertices, edges, src, dest, start, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    for (i = 0; i < vertices; i++)
        for (j = 0; j < vertices; j++)
            adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (source destination):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        adj[src][dest] = 1;
        adj[dest][src] = 1;
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    BFS(vertices, start);
    return 0;
}
