#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 50

struct Graph {
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
};

struct Node {
    int data;
    struct Node *next;
} *front = NULL, *rear = NULL;

void enqueue(int x) {
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
        printf("Queue is full\n");
    else {
        newNode->data = x;
        newNode->next = NULL;
        if (front == NULL)
            front = rear = newNode;
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }
}

int dequeue() {
    int x = -1;
    struct Node *tempNode;

    if (front == NULL)
        printf("Queue is empty\n");
    else {
        x = front->data;
        tempNode = front;
        front = front->next;
        free(tempNode);
    }
    return x;
}

int isEmptyQueue() {
    return front == NULL;
}

void initializeGraph(struct Graph *graph, int vertices) {
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++)
            graph->adjacencyMatrix[i][j] = 0;
    }
}

void addEdge(struct Graph *graph, int vertex1, int vertex2) {
    if (vertex1 >= 0 && vertex1 < graph->numVertices && vertex2 >= 0 && vertex2 < graph->numVertices) {
        graph->adjacencyMatrix[vertex1][vertex2] = 1;
        graph->adjacencyMatrix[vertex2][vertex1] = 1;
    } else {
        printf("Invalid vertex indices!\n");
    }
}

void breadthFirstSearch(struct Graph *graph, int startVertex) {
    int currentVertex;
    int visited[MAX_VERTICES] = {0};

    printf("\nBreadth First Search Traversal from starting vertex %d:\n", startVertex);
    visited[startVertex] = 1;
    enqueue(startVertex);

    while (!isEmptyQueue()) {
        currentVertex = dequeue();
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjacencyMatrix[currentVertex][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                enqueue(i);
            }
        }
    }
    printf("\n");
}

void printGraph(struct Graph *graph) {
    printf("\nAdjacency Matrix Representation of the Graph:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    int numVertices, numEdges, startVertex, vertex1, vertex2, choice;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    initializeGraph(graph, numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges:\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &vertex1, &vertex2);
        addEdge(graph, vertex1, vertex2);
    }

    while (1) {
        printf("\n1. Breadth First Search Traversal\n2. Print Adjacency Matrix\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the starting vertex: ");
                scanf("%d", &startVertex);
                breadthFirstSearch(graph, startVertex);
                break;
            case 2:
                printGraph(graph);
                break;
            case 3:
                free(graph);
                exit(0);
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
