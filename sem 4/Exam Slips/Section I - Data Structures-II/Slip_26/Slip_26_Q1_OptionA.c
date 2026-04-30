/* Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency
   matrix. Implement function to traverse the graph using Depth First Search (DFS) traversal. */

#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];

void DFS(int vertices, int vertex) {
    int i;
    printf("%d ", vertex);
    visited[vertex] = 1;
    for (i = 0; i < vertices; i++) {
        if (adj[vertex][i] == 1 && !visited[i])
            DFS(vertices, i);
    }
}

int main() {
    int vertices, edges, src, dest, start, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    for (i = 0; i < vertices; i++) {
        visited[i] = 0;
        for (j = 0; j < vertices; j++) adj[i][j] = 0;
    }

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

    printf("DFS Traversal starting from vertex %d: ", start);
    DFS(vertices, start);
    printf("\n");

    return 0;
}
