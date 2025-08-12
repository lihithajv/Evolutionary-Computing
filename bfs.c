#include <stdio.h>
#include <stdlib.h>

#define MAX 10   // Max number of vertices

// Queue variables
int queue[MAX], front = -1, rear = -1;

void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue overflow\n");
        return;
    }
    if (front == -1) front = 0;
    queue[++rear] = value;
}

int dequeue() {
    if (front == -1 || front > rear) {
        return -1; // Empty queue
    }
    return queue[front++];
}

int isEmpty() {
    return (front == -1 || front > rear);
}

// BFS that finds and prints path from start to goal
void bfs_path(int graph[MAX][MAX], int start, int goal, int n) {
    int visited[MAX] = {0};
    int parent[MAX]; // To store path
    int i;

    for (i = 0; i < n; i++) parent[i] = -1;

    enqueue(start);
    visited[start] = 1;
    parent[start] = -1; // Start has no parent

    while (!isEmpty()) {
        int node = dequeue();

        if (node == goal) {
            // Reconstruct path
            int path[MAX], path_len = 0;
            int temp = goal;
            while (temp != -1) {
                path[path_len++] = temp;
                temp = parent[temp];
            }

            // Print path in reverse order
            printf("Path from start to goal: ");
            for (i = path_len - 1; i >= 0; i--) {
                printf("%d ", path[i]);
            }
            printf("\n");
            return; // Stop BFS after finding goal
        }

        for (i = 0; i < n; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
                parent[i] = node; // Store parent
            }
        }
    }

    printf("Goal not reachable from start.\n");
}

int main() {
    int n = 7; // Number of vertices: S=0, A=1, B=2, C=3, R=4, D=5, G=6
    int graph[MAX][MAX] = {0};

    // Edges from the image
    graph[0][1] = 1; // S -> A
    graph[0][2] = 1; // S -> B
    graph[1][2] = 1; // A -> B
    graph[1][5] = 1; // A -> D
    graph[2][3] = 1; // B -> C
    graph[3][4] = 1; // C -> R
    graph[5][6] = 1; // D -> G

    int start = 0; // S
    int goal = 6;  // G

    bfs_path(graph, start, goal, n);

    return 0;
}