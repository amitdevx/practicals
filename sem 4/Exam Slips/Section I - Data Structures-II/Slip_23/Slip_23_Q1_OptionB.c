/* Q1) Write a C program for the implementation of Topological sorting. */

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX];
int visited[MAX];
int stack[MAX], top = -1;

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

void topologicalSortUtil(int v) {
    Node* temp;
    visited[v] = 1;
    temp = adjList[v];
    while (temp != NULL) {
        if (!visited[temp->vertex])
            topologicalSortUtil(temp->vertex);
        temp = temp->next;
    }
    stack[++top] = v;
}

int main() {
    int vertices, edges, src, dest, i;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    for (i = 0; i < vertices; i++) { adjList[i] = NULL; visited[i] = 0; }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (source destination) for directed graph:\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(src, dest);
    }

    for (i = 0; i < vertices; i++) {
        if (!visited[i])
            topologicalSortUtil(i);
    }

    printf("Topological Sort: ");
    while (top >= 0) printf("%d ", stack[top--]);
    printf("\n");

    for (i = 0; i < vertices; i++) {
        Node* temp = adjList[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    return 0;
}
