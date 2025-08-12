#include <stdio.h>
#include <stdlib.h>

#define MAX 10 // Max number of vertices

// ===== Queue for BFS =====
int queue[MAX], front = -1, rear = -1;

void enqueue(int value) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = value;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

int isEmpty() {
    return (front == -1 || front > rear);
}

// ===== Find Path using BFS =====
void find_path_bfs(int graph[MAX][MAX], int start, int goal, int n) {
    int visited[MAX] = {0};
    int parent[MAX]; // Store parent of each node
    for (int i = 0; i < n; i++) parent[i] = -1;

    front = rear = -1;
    enqueue(start);
    visited[start] = 1;

    int found = 0;

    while (!isEmpty()) {
        int node = dequeue();

        if (node == goal) {
            found = 1;
            break;
        }

        for (int i = 0; i < n; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
                parent[i] = node; // Track how we got here
            }
        }
    }

    if (!found) {
        printf("No path found from %d to %d\n", start, goal);
        return;
    }

    // Reconstruct path
    int path[MAX], path_len = 0;
    for (int v = goal; v != -1; v = parent[v]) {
        path[path_len++] = v;
    }

    // Print path in correct order
    printf("Path from %d to %d: ", start, goal);
    for (int i = path_len - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

// ===== Main =====
int main() {
    int n = 6; // Number of vertices
    int graph[MAX][MAX] = {0};

    // Example graph (A=0, B=1, C=2, D=3, E=4, F=5)
    graph[0][1] = 1; // A -> B
    graph[0][2] = 1; // A -> C
    graph[1][3] = 1; // B -> D
    graph[1][4] = 1; // B -> E
    graph[2][5] = 1; // C -> F
    graph[4][5] = 1; // E -> F

    int start = 0; // A
    int goal = 5;  // F

    find_path_bfs(graph, start, goal, n);

    return 0;
}