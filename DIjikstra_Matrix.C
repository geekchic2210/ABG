#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];
int num_vertices;

void initializeGraph() {
    int i, j;
    for (i = 0; i < MAX_VERTICES; i++) {
        for (j = 0; j < MAX_VERTICES; j++) {
            graph[i][j] = 0;
        }
    }
}

void addEdge(int u, int v, int weight) {
    graph[u][v] = weight;
    graph[v][u] = weight; 
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

        for (j = 0; j < num_vertices; j++) {
            if (!visited[j] && graph[min_index][j] && dist[min_index] != INT_MAX &&
                dist[min_index] + graph[min_index][j] < dist[j]) {
                dist[j] = dist[min_index] + graph[min_index][j];
            }
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

    return 0;
}
