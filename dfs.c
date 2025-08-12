#include <stdio.h>

#define V 7  // Number of vertices

int graph[V][V];   // Adjacency matrix
int visited[V];    // Visited array
int path[V];       // To store the current path
int pathIndex = 0; // Path length tracker
int found = 0;     // To stop when goal is found

void addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1; // Undirected graph
}

void printPath(int length) {
    printf("Path: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void DFS(int current, int goal) {
    visited[current] = 1;
    path[pathIndex++] = current;

    if (current == goal) {
        printPath(pathIndex);
        found = 1;
        return;
    }

    for (int i = 0; i < V; i++) {
        if (graph[current][i] && !visited[i]) {
            DFS(i, goal);
            if (found) return; // Stop search when goal found
        }
    }

    pathIndex--; // Backtrack
    visited[current] = 0; // Allow other paths if needed
}

int main() {
    // Initialize adjacency matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    // Create a sample graph (7 edges)
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 5);
    addEdge(3, 6);
    addEdge(4, 6);

    int start = 0, goal = 6;

    printf("DFS Path from %d to %d:\n", start, goal);
    DFS(start, goal);

    if (!found)
        printf("No path found.\n");

    return 0;
}