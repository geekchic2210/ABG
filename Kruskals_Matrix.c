#include <stdio.h>
#include <stdlib.h>


struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
    return graph;
}

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

int compare(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare);

    int parent[V];
    for (int v = 0; v < V; ++v)
        parent[v] = -1;

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
    }

    printf("Minimum Spanning Tree (Kruskal's Algorithm):\n");
    int minimumCost = 0;
    for (int i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost Spanning Tree: %d\n", minimumCost);
}

void addEdges(struct Graph* graph) {
    printf("Enter the number of edges: ");
    scanf("%d", &(graph->E));
    graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));

    printf("Enter source, destination and weight for each edge:\n");
    for (int i = 0; i < graph->E; ++i) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &(graph->edge[i].src), &(graph->edge[i].dest), &(graph->edge[i].weight));
    }
}

void freeGraph(struct Graph* graph) {
    free(graph->edge);
    free(graph);
}


void displayMenu() {
    printf("\nMENU:\n");
    printf("1. Add edges to the graph\n");
    printf("2. Find Minimum Spanning Tree (Kruskal's Algorithm)\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}


int main() {
    struct Graph* graph = NULL;
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (graph != NULL) {
                    freeGraph(graph);
                }
                int V;
                printf("Enter the number of vertices: ");
                scanf("%d", &V);
                graph = createGraph(V, 0);
                addEdges(graph);
                break;
            case 2:
                if (graph == NULL) {
                    printf("Graph not initialized. Please add edges first.\n");
                } else {
                    KruskalMST(graph);
                }
                break;
            case 3:
                printf("Exiting...\n");
                if (graph != NULL) {
                    freeGraph(graph);
                }
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}
