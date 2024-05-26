#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} List;

List* adjacencyList[MAX_VERTICES];
int num_vertices;

void initializeGraph() {
    int i;
    for (i = 0; i < MAX_VERTICES; i++) {
        adjacencyList[i] = NULL;
    }
}

Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int u, int v, int weight) {
    Node* newNode = createNode(v, weight);
    newNode->next = adjacencyList[u]->head;
    adjacencyList[u]->head = newNode;

    newNode = createNode(u, weight); 
    newNode->next = adjacencyList[v]->head;
    adjacencyList[v]->head = newNode;
}

void dijkstra(int source) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int i, j, min_index, min_dist;

    for (i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (i = 0; i < num_vertices - 1; i++) {
        min_dist = INT_MAX;
        for (j = 0; j < num_vertices; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                min_index = j;
            }
        }

        visited[min_index] = 1;

        Node* temp = adjacencyList[min_index]->head;
        while (temp != NULL) {
            if (!visited[temp->vertex] && dist[min_index] != INT_MAX &&
                dist[min_index] + temp->weight < dist[temp->vertex]) {
                dist[temp->vertex] = dist[min_index] + temp->weight;
            }
            temp = temp->next;
        }
    }

    printf("Vertex   Distance from Source\n");
    for (i = 0; i < num_vertices; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d \t\t Infinity\n", i);
        } else {
            printf("%d \t\t %d\n", i, dist[i]);
        }
    }
}

int main() {
    int choice, source, u, v, weight;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &num_vertices);

    initializeGraph();

    for (int i = 0; i < num_vertices; i++) {
        adjacencyList[i] = (List*)malloc(sizeof(List));
        adjacencyList[i]->head = NULL;
    }

    do {
        printf("\n1. Add Edge\n");
        printf("2. Find Shortest Path (Dijkstra's Algorithm)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter edge (u, v) and weight: ");
                scanf("%d %d %d", &u, &v, &weight);
                if (adjacencyList[u] == NULL) {
                    adjacencyList[u] = (List*)malloc(sizeof(List));
                    adjacencyList[u]->head = NULL;
                }
                if (adjacencyList[v] == NULL) {
                    adjacencyList[v] = (List*)malloc(sizeof(List));
                    adjacencyList[v]->head = NULL;
                }
                addEdge(u, v, weight);
                break;
            case 2:
                printf("Enter the source vertex: ");
                scanf("%d", &source);
                dijkstra(source);
                break;
            case 3:
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    for (int i = 0; i < num_vertices; i++) {
        Node* temp = adjacencyList[i]->head;
        while (temp != NULL) {
            Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
        free(adjacencyList[i]);
    }

    return 0;
}
