/* Q1) Write a C program for the Implementation of Prim's Minimum spanning tree algorithm. */

#include <stdio.h>
#include <limits.h>

#define MAX 20
#define INF INT_MAX

int minKey(int key[], int mstSet[], int vertices) {
    int min = INF, min_index = 0, v;
    for (v = 0; v < vertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void primMST(int graph[MAX][MAX], int vertices) {
    int parent[MAX], key[MAX], mstSet[MAX];
    int i, count, u, v, totalWeight = 0;

    for (i = 0; i < vertices; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;

    for (count = 0; count < vertices - 1; count++) {
        u = minKey(key, mstSet, vertices);
        mstSet[u] = 1;
        for (v = 0; v < vertices; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("\nEdge \tWeight\n");
    for (i = 1; i < vertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("Total Weight of MST: %d\n", totalWeight);
}

int main() {
    int graph[MAX][MAX], vertices, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (i = 0; i < vertices; i++)
        for (j = 0; j < vertices; j++)
            scanf("%d", &graph[i][j]);

    primMST(graph, vertices);
    return 0;
}
