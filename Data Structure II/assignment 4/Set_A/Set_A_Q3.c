/*
 * Assignment 4 - Set A - Question 3
 * 
 * Write a C program for the Implementation of Kruskal's Minimum spanning tree algorithm.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Graph {
    int V, E;
    Edge edge[MAX];
} Graph;

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    
    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int compare(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight - b1->weight;
}

void kruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[MAX];
    int e = 0;
    int i = 0;
    
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare);
    
    int parent[MAX];
    int rank[MAX];
    
    for (int v = 0; v < V; v++) {
        parent[v] = v;
        rank[v] = 0;
    }
    
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edge[i++];
        
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);
        
        if (x != y) {
            result[e++] = next_edge;
            unionSets(parent, rank, x, y);
        }
    }
    
    printf("\nEdges in MST:\n");
    printf("Edge \tWeight\n");
    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total Weight of MST: %d\n", totalWeight);
}

int main() {
    Graph g;
    
    printf("Enter number of vertices: ");
    scanf("%d", &g.V);
    
    printf("Enter number of edges: ");
    scanf("%d", &g.E);
    
    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < g.E; i++) {
        scanf("%d %d %d", &g.edge[i].src, &g.edge[i].dest, &g.edge[i].weight);
    }
    
    kruskalMST(&g);
    
    return 0;
}
