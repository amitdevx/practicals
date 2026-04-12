/* Q1) Write a C program for the implementation of Dijkstra's shortest path algorithm for finding
   shortest path from a given source vertex using adjacency cost matrix. */

#include <stdio.h>
#include <limits.h>

#define MAX 20
#define INF INT_MAX

void dijkstra(int graph[MAX][MAX], int vertices, int src) {
    int dist[MAX], visited[MAX];
    int i, count, u, v;
    int min, min_index;

    for (i = 0; i < vertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (count = 0; count < vertices - 1; count++) {
        min = INF; min_index = 0;
        for (v = 0; v < vertices; v++) {
            if (visited[v] == 0 && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        u = min_index;
        visited[u] = 1;

        for (v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    printf("\nVertex \t Distance from Source %d\n", src);
    for (i = 0; i < vertices; i++) {
        printf("%d \t ", i);
        if (dist[i] == INF) printf("INF\n");
        else printf("%d\n", dist[i]);
    }
}

int main() {
    int graph[MAX][MAX], vertices, src, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter adjacency cost matrix (0 for no edge):\n");
    for (i = 0; i < vertices; i++)
        for (j = 0; j < vertices; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, vertices, src);
    return 0;
}
