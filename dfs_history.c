#include <stdio.h>

#define MAX_NODES 100

int visited[MAX_NODES];
int graph[MAX_NODES][MAX_NODES];
int n; // number of nodes

void DFS(int node) {
    int i;
    visited[node] = 1;
    printf("%d ", node);

    for (i = 0; i < n; i++) {
        if (graph[node][i] == 1 && visited[i] == 0) {
            DFS(i);
        }
    }
}

int main() {
    int i, j, edges, src, dest;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    // Initialize adjacency matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge as: source destination\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        graph[src][dest] = 1;
        graph[dest][src] = 1; // remove if directed graph
    }

    // Initialize visited array
    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("DFS Traversal with History (no revisits):\n");
    DFS(0); // starting from node 0

    return 0;
}