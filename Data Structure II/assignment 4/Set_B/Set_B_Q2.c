/*
 * Assignment 4 - Set B - Question 2
 * 
 * Write a C program for the implementation of Floyd Warshall's algorithm for finding all pairs
 * shortest path using adjacency cost matrix.
 */

#include <stdio.h>
#include <limits.h>

#define MAX 20
#define INF 99999

void printSolution(int dist[MAX][MAX], int vertices) {
    printf("\nShortest distances between every pair of vertices:\n");
    printf("    ");
    for (int i = 0; i < vertices; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    for (int i = 0; i < vertices; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INF) {
                printf(" INF");
            } else {
                printf("%4d", dist[i][j]);
            }
        }
        printf("\n");
    }
}

void floydWarshall(int graph[MAX][MAX], int vertices) {
    int dist[MAX][MAX];
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            dist[i][j] = graph[i][j];
        }
    }
    
    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    printSolution(dist, vertices);
}

int main() {
    int graph[MAX][MAX];
    int vertices;
    
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    printf("Enter adjacency cost matrix (Use 99999 for INF):\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    floydWarshall(graph, vertices);
    
    return 0;
}
