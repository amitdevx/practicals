/* Q1) Write a C program that accepts the vertices and edges of a graph. Create and display adjacency
   list also print indegree, outdegree and total degree of all vertex of graph. */

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

void displayAdjList(int vertices) {
    int i;
    printf("\nAdjacency List:\n");
    for (i = 0; i < vertices; i++) {
        Node* temp = adjList[i];
        printf("%d: ", i);
        while (temp != NULL) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void calculateDegrees(int vertices) {
    int outdegree[MAX] = {0}, indegree[MAX] = {0};
    int i;
    Node* temp;

    for (i = 0; i < vertices; i++) {
        temp = adjList[i];
        while (temp != NULL) {
            outdegree[i]++;
            indegree[temp->vertex]++;
            temp = temp->next;
        }
    }

    printf("\nVertex | OutDegree | InDegree | Total Degree\n");
    printf("-------|-----------|----------|-------------\n");
    for (i = 0; i < vertices; i++) {
        printf("  %d    |     %d     |    %d     |      %d\n",
               i, outdegree[i], indegree[i], outdegree[i] + indegree[i]);
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
    int vertices, edges, src, dest, directed, i;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    for (i = 0; i < vertices; i++) adjList[i] = NULL;

    printf("Is graph directed? (1=Yes, 0=No): ");
    scanf("%d", &directed);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (source destination):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(src, dest);
        if (!directed) addEdge(dest, src);
    }

    displayAdjList(vertices);
    calculateDegrees(vertices);
    freeList(vertices);
    return 0;
}
