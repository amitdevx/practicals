/*
 * Assignment 3 - Set A - Question 1
 * 
 * Write a C program that accepts the vertices and edges of a graph and stores it as an adjacency matrix.
 * Display the adjacency matrix.
 */

#include <stdio.h>

#define MAX 20

void createGraph(int adj[MAX][MAX], int vertices) {
    int i, j;
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            adj[i][j] = 0;
        }
    }
}

void addEdge(int adj[MAX][MAX], int src, int dest) {
    adj[src][dest] = 1;
}

void displayMatrix(int adj[MAX][MAX], int vertices) {
    printf("\nAdjacency Matrix:\n");
    printf("   ");
    for (int i = 0; i < vertices; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < vertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < vertices; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int adj[MAX][MAX];
    int vertices, edges, src, dest, i;
    int directed;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    createGraph(adj, vertices);

    printf("Is graph directed? (1=Yes, 0=No): ");
    scanf("%d", &directed);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (source destination):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(adj, src, dest);
        if (!directed) {
            addEdge(adj, dest, src);
        }
    }

    displayMatrix(adj, vertices);

    return 0;
}
