#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define m 20

struct node {
    int vertex;
    int weight;
    struct node *next;
};

struct Graph {
    struct node *adjList[m];
    int V;
};

void init(struct Graph *g, int v) {
    g->V = v;
    for (int i = 0; i < v; i++) {
        g->adjList[i] = NULL;
    }
}

void addEdge(struct Graph *g, int src, int dest, int weight) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;

    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->vertex = src;
    newNode->weight = weight;
    newNode->next = g->adjList[dest];
    g->adjList[dest] = newNode;
}

int minKey(int key[], int visited[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (visited[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

void printMST(int p[],int d[], struct Graph* g) {
    printf("Edge\tWeight\n");
    for (int i = 1; i < g->V; i++) {
         if  (p[i] != -1){
        printf("%d - %d\t%d\n", p[i], i, d[i]);
    }
}
}

void primMST(struct Graph* g, int st) {
    int p[m];
    int d[m];
    int visited[m];
    for (int i = 0; i < g->V; i++) {
        d[i] = INT_MAX;
        visited[i] = 0;
        p[i] = -1;
    }

    d[st] = 0;

    for (int count = 0; count < g->V - 1; count++) {
        int u = minKey(d, visited, g->V);
        visited[u] = 1;

        struct node *temp = g->adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (visited[v] == 0 && weight < d[v]) {
                p[v] = u;
                d[v] = weight;
            }
            temp = temp->next;
        }
    }
   printMST(p,d,g);
   
}


void Print(struct Graph *g) {
    printf("Adjacency List Representation of Graph:\n");
    for (int i = 0; i < g->V; ++i) {
        printf("Vertex %d: ", i);
        struct node *temp = g->adjList[i];
        while (temp != NULL) {
            printf("(%d, %d) -> ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
    int v, e, a, b, w, ch,st;
    printf("Enter the number of Vertices: ");
    scanf("%d", &v);
    init(g, v);

    printf("Enter the number of Edges: ");
    scanf("%d", &e);

    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &a, &b, &w);
        addEdge(g, a, b, w);
    }

    while (1) {
        printf("\n1.Print Adjacency List\n2.Prims Algorithm for Minimum Spanning Tree\n3.Exit\nEnter Your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            printf("\n");
            Print(g);
            break;

        case 2:
            printf("Enter the starting Vertex: ");
            scanf("%d",&st);
            if (st < 0 || st >= g->V) {
                printf("Invalid starting vertex!\n");
            } else {
                printf("Minimum Spanning Tree using Prim's Algorithm:\n");
                primMST(g,st);
            }
            break;

        case 3:
            free(g);
            exit(0);
            break;

        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    }
    return 0;
}