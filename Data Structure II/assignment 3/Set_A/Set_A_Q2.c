/*
 * Assignment 3 - Set A - Question 2
 * 
 * Write a C program that accepts the vertices and edges of a graph. Create and display
 * adjacency list also print indegree, outdegree and total degree of all vertex of graph.
 */

#include <stdio.h>
#include <stdlib.h>

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

void displayAdjList(Node* adj[], int vertices) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d: ", i);
        Node* temp = adj[i];
        while (temp != NULL) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void calculateDegrees(Node* adj[], int vertices, int directed) {
    int outdegree[vertices], indegree[vertices];
    
    for (int i = 0; i < vertices; i++) {
        outdegree[i] = 0;
        indegree[i] = 0;
    }
    
    for (int i = 0; i < vertices; i++) {
        Node* temp = adj[i];
        while (temp != NULL) {
            outdegree[i]++;
            indegree[temp->vertex]++;
            temp = temp->next;
        }
    }
    
    printf("\nDegree Information:\n");
    printf("Vertex | OutDegree | InDegree | Total Degree\n");
    printf("-------|-----------|----------|-------------\n");
    
    for (int i = 0; i < vertices; i++) {
        if (directed) {
            printf("  %d    |     %d     |    %d     |      %d\n", 
                   i, outdegree[i], indegree[i], outdegree[i] + indegree[i]);
        } else {
            printf("  %d    |           |          |      %d\n", i, outdegree[i]);
        }
    }
}

int main() {
    int vertices, edges, src, dest, directed;
    
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    Node* adj[vertices];
    for (int i = 0; i < vertices; i++) {
        adj[i] = NULL;
    }
    
    printf("Is graph directed? (1=Yes, 0=No): ");
    scanf("%d", &directed);
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(adj, src, dest);
        if (!directed) {
            addEdge(adj, dest, src);
        }
    }
    
    displayAdjList(adj, vertices);
    calculateDegrees(adj, vertices, directed);
    
    return 0;
}
