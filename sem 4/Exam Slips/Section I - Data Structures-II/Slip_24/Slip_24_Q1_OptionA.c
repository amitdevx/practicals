/* Q1) Write a C program for the implementation of Floyd Warshall's algorithm for finding all pairs
   shortest path using adjacency cost matrix. */

#include <stdio.h>

#define MAX 20
#define INF 99999

void floydWarshall(int graph[MAX][MAX], int vertices) {
    int dist[MAX][MAX];
    int i, j, k;

    for (i = 0; i < vertices; i++)
        for (j = 0; j < vertices; j++)
            dist[i][j] = graph[i][j];

    for (k = 0; k < vertices; k++)
        for (i = 0; i < vertices; i++)
            for (j = 0; j < vertices; j++)
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    printf("\nShortest distances between every pair of vertices:\n    ");
    for (i = 0; i < vertices; i++) printf("%4d", i);
    printf("\n");
    for (i = 0; i < vertices; i++) {
        printf("%2d: ", i);
        for (j = 0; j < vertices; j++) {
            if (dist[i][j] == INF) printf(" INF");
            else printf("%4d", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int graph[MAX][MAX], vertices, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter adjacency cost matrix (Use 99999 for INF):\n");
    for (i = 0; i < vertices; i++)
        for (j = 0; j < vertices; j++)
            scanf("%d", &graph[i][j]);

    floydWarshall(graph, vertices);
    return 0;
}
