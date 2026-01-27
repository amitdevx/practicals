/*
 * Assignment 4 - Set A - Question 1
 * 
 * Write a C program for the implementation of Topological sorting.
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

void topologicalSortUtil(Node* adj[], int v, int visited[], int stack[], int *top) {
    visited[v] = 1;
    
    Node* temp = adj[v];
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            topologicalSortUtil(adj, temp->vertex, visited, stack, top);
        }
        temp = temp->next;
    }
    
    stack[++(*top)] = v;
}

void topologicalSort(Node* adj[], int vertices) {
    int visited[MAX] = {0};
    int stack[MAX];
    int top = -1;
    
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(adj, i, visited, stack, &top);
        }
    }
    
    printf("Topological Sort: ");
    while (top >= 0) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}

int main() {
    int vertices, edges, src, dest;
    
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    Node* adj[vertices];
    for (int i = 0; i < vertices; i++) {
        adj[i] = NULL;
    }
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter edges (source destination) for directed graph:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(adj, src, dest);
    }
    
    topologicalSort(adj, vertices);
    
    return 0;
}
