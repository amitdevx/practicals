/* Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency list.
   Implement function to traverse the graph using Breadth First Search (BFS) traversal. */

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX];

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

void BFS(int vertices, int start) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    int vertex;
    Node* temp;

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS Traversal starting from vertex %d: ", start);
    while (front < rear) {
        vertex = queue[front++];
        printf("%d ", vertex);
        temp = adjList[vertex];
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
    for (i = 0; i < vertices; i++) adjList[i] = NULL;

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

    BFS(vertices, start);
    freeList(vertices);
    return 0;
}
