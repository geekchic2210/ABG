#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent an adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct Node* head;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct AdjList* array;
    int* visited;
};

// Function to create a new adjacency list node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of a given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->array = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));
    graph->visited = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Add an edge from dest to src (since the graph is undirected)
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to perform DFS traversal
void DFS(struct Graph* graph, int vertex) {
    struct Node* adjList = graph->array[vertex].head;
    struct Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// Function to reset the visited array for new DFS traversal
void resetVisited(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

// Function to display the adjacency list of the graph
void displayAdjList(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->array[v].head;
        printf("\n Vertex %d\n head ", v);
        while (temp) {
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Create Graph\n");
    printf("2. Display Adjacency List\n");
    printf("3. Perform DFS Traversal\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Graph* graph = NULL;
    int choice, numVertices, src, dest, startVertex;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of vertices: ");
                scanf("%d", &numVertices);
                graph = createGraph(numVertices);
                printf("Enter number of edges: ");
                int numEdges;
                scanf("%d", &numEdges);
                for (int i = 0; i < numEdges; i++) {
                    printf("Enter edge %d (source and destination): ", i + 1);
                    scanf("%d %d", &src, &dest);
                    addEdge(graph, src, dest);
                }
                break;
            case 2:
                if (graph == NULL) {
                    printf("Graph not created yet!\n");
                } else {
                    displayAdjList(graph);
                }
                break;
            case 3:
                if (graph == NULL) {
                    printf("Graph not created yet!\n");
                } else {
                    printf("Enter starting vertex for DFS: ");
                    scanf("%d", &startVertex);
                    if (startVertex < 0 || startVertex >= numVertices) {
                        printf("Invalid starting vertex!\n");
                    } else {
                        printf("DFS Traversal: ");
                        resetVisited(graph);
                        DFS(graph, startVertex);
                        printf("\n");
                    }
                }
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
