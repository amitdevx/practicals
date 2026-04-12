/* Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency list.
   Implement function to traverse the graph using Depth First Search (DFS) traversal. */

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX];
int visited[MAX];

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = adjList[src];
    adjList[src] = newNode;
}

void DFS(int vertex) {
    Node* temp;
    printf("%d ", vertex);
    visited[vertex] = 1;
    temp = adjList[vertex];
    while (temp != NULL) {
        if (!visited[temp->vertex])
            DFS(temp->vertex);
        temp = temp->next;
    }
}

void freeList(int vertices) {
    int i;
    for (i = 0; i < vertices; i++) {
        Node* temp = adjList[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
}

int main() {
    int vertices, edges, src, dest, start, i;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    for (i = 0; i < vertices; i++) { adjList[i] = NULL; visited[i] = 0; }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (source destination):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(src, dest);
        addEdge(dest, src);
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    printf("DFS Traversal starting from vertex %d: ", start);
    DFS(start);
    printf("\n");

    freeList(vertices);
    return 0;
}
