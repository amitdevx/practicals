/*
 * Assignment 3 - Set B - Question 1
 * 
 * Write a C program that accepts the vertices and edges of a graph and store it as an adjacency
 * matrix. Implement function to traverse the graph using Breadth First Search (BFS) and Depth
 * First Search (DFS) traversal.
 */

#include <stdio.h>

#define MAX 20

void createGraph(int adj[MAX][MAX], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adj[i][j] = 0;
        }
    }
}

void addEdge(int adj[MAX][MAX], int src, int dest) {
    adj[src][dest] = 1;
}

void DFS(int adj[MAX][MAX], int vertices, int visited[], int vertex) {
    printf("%d ", vertex);
    visited[vertex] = 1;
    
    for (int i = 0; i < vertices; i++) {
        if (adj[vertex][i] == 1 && !visited[i]) {
            DFS(adj, vertices, visited, i);
        }
    }
}

void BFS(int adj[MAX][MAX], int vertices, int start) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    
    visited[start] = 1;
    queue[rear++] = start;
    
    printf("BFS Traversal: ");
    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);
        
        for (int i = 0; i < vertices; i++) {
            if (adj[vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

int main() {
    int adj[MAX][MAX];
    int vertices, edges, src, dest, start;
    
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    createGraph(adj, vertices);
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(adj, src, dest);
        addEdge(adj, dest, src);
    }
    
    printf("Enter starting vertex: ");
    scanf("%d", &start);
    
    int visited[MAX] = {0};
    printf("DFS Traversal: ");
    DFS(adj, vertices, visited, start);
    printf("\n");
    
    BFS(adj, vertices, start);
    
    return 0;
}
