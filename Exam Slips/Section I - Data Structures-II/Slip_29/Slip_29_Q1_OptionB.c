/* Q1) Write a C program for the Implementation of Kruskal's Minimum spanning tree algorithm. */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct { int src, dest, weight; } Edge;

int parent[MAX];

int find(int i) {
    if (parent[i] == i) return i;
    return find(parent[i]);
}

void unionSets(int x, int y) {
    int xroot = find(x), yroot = find(y);
    parent[xroot] = yroot;
}

int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int main() {
    Edge edges[MAX], result[MAX];
    int V, E, i, e = 0, idx = 0, totalWeight = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (source destination weight):\n");
    for (i = 0; i < E; i++)
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);

    qsort(edges, E, sizeof(Edge), compare);
    for (i = 0; i < V; i++) parent[i] = i;

    while (e < V - 1 && idx < E) {
        Edge next = edges[idx++];
        int x = find(next.src), y = find(next.dest);
        if (x != y) {
            result[e++] = next;
            unionSets(x, y);
        }
    }

    printf("\nEdges in MST:\nEdge \tWeight\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total Weight of MST: %d\n", totalWeight);
    return 0;
}
