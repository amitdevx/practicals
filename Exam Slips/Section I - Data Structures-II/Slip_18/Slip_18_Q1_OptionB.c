/* Q1) Write a C program that accepts the vertices and edges of a graph and stores it as an adjacency
   matrix. Display the adjacency matrix. */

#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];

void createGraph(int vertices) {
    int i, j;
    for (i = 0; i < vertices; i++)
        for (j = 0; j < vertices; j++)
            adj[i][j] = 0;
}

void addEdge(int src, int dest) {
    adj[src][dest] = 1;
}

void displayMatrix(int vertices) {
    int i, j;
    printf("\nAdjacency Matrix:\n   ");
    for (i = 0; i < vertices; i++) printf("%d ", i);
    printf("\n");
    for (i = 0; i < vertices; i++) {
        printf("%d: ", i);
        for (j = 0; j < vertices; j++) printf("%d ", adj[i][j]);
        printf("\n");
    }
}

int main() {
    int vertices, edges, src, dest, i, directed;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    createGraph(vertices);

    printf("Is graph directed? (1=Yes, 0=No): ");
    scanf("%d", &directed);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (source destination):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(src, dest);
        if (!directed) addEdge(dest, src);
    }

    displayMatrix(vertices);
    return 0;
}
