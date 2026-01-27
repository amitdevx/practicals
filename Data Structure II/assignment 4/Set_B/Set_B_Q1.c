/*
 * Assignment 4 - Set B - Question 1
 * 
 * Write a C program for the implementation of Dijkstra's shortest path algorithm for finding
 * shortest path from a given source vertex using adjacency cost matrix.
 */

#include <stdio.h>
#include <limits.h>

#define MAX 20
#define INF INT_MAX

int minDistance(int dist[], int visited[], int vertices) {
    int min = INF, min_index;
    
    for (int v = 0; v < vertices; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printSolution(int dist[], int vertices, int src) {
    printf("\nVertex \t Distance from Source %d\n", src);
    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INF) {
            printf("%d \t INF\n", i);
        } else {
            printf("%d \t %d\n", i, dist[i]);
        }
    }
}

void dijkstra(int graph[MAX][MAX], int vertices, int src) {
    int dist[MAX];
    int visited[MAX];
    
    for (int i = 0; i < vertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    
    dist[src] = 0;
    
    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, visited, vertices);
        visited[u] = 1;
        
        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && 
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    
    printSolution(dist, vertices, src);
}

int main() {
    int graph[MAX][MAX];
    int vertices, src;
    
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    printf("Enter adjacency cost matrix (0 for no edge):\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    printf("Enter source vertex: ");
    scanf("%d", &src);
    
    dijkstra(graph, vertices, src);
    
    return 0;
}
