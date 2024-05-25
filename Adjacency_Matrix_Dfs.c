#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjMatrix[MAX][MAX];
int visited[MAX];
int n; // number of vertices

// Function to initialize the adjacency matrix and visited array
void initialize() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            adjMatrix[i][j] = 0;
        }
        visited[i] = 0;
    }
}

// Function to create the adjacency matrix
void createGraph() {
    int i, origin, dest, edges;
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    initialize();
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    for (i = 0; i < edges; i++) {
        printf("Enter edge %d (origin and destination): ", i + 1);
        scanf("%d %d", &origin, &dest);
        
        if (origin >= n || dest >= n || origin < 0 || dest < 0) {
            printf("Invalid edge!\n");
            i--;
        } else {
            adjMatrix[origin][dest] = 1;
            adjMatrix[dest][origin] = 1; // Assuming it's an undirected graph
        }
    }
}

// Function to perform DFS traversal
void DFS(int vertex) {
    int i;
    printf("%d ", vertex);
    visited[vertex] = 1;
    
    for (i = 0; i < n; i++) {
        if (adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

// Function to reset the visited array for new DFS traversal
void resetVisited() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}

// Function to display the adjacency matrix
void displayAdjMatrix() {
    int i, j;
    printf("Adjacency Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Create Graph\n");
    printf("2. Display Adjacency Matrix\n");
    printf("3. Perform DFS Traversal\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, startVertex;
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createGraph();
                break;
            case 2:
                displayAdjMatrix();
                break;
            case 3:
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &startVertex);
                if (startVertex < 0 || startVertex >= n) {
                    printf("Invalid starting vertex!\n");
                } else {
                    printf("DFS Traversal: ");
                    resetVisited();
                    DFS(startVertex);
                    printf("\n");
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
