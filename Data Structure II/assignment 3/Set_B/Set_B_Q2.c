/*
 * Assignment 3 - Set B - Question 2
 * 
 * Write a C program that accepts the vertices and edges of a graph and store it as an adjacency list.
 * Implement function to traverse the graph using Breadth First Search (BFS) and Depth First
 * Search (DFS) traversal.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Node* adj[], int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = adj[src];
    adj[src] = newNode;
}

void DFS(Node* adj[], int visited[], int vertex) {
    printf("%d ", vertex);
    visited[vertex] = 1;
    
    Node* temp = adj[vertex];
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            DFS(adj, visited, temp->vertex);
        }
        temp = temp->next;
    }
}

void BFS(Node* adj[], int vertices, int start) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    
    visited[start] = 1;
    queue[rear++] = start;
    
    printf("BFS Traversal: ");
    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);
        
        Node* temp = adj[vertex];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                queue[rear++] = temp->vertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main() {
    int vertices, edges, src, dest, start;
    
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    Node* adj[vertices];
    for (int i = 0; i < vertices; i++) {
        adj[i] = NULL;
    }
    
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
    DFS(adj, visited, start);
    printf("\n");
    
    BFS(adj, vertices, start);
    
    return 0;
}
