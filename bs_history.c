#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int node;
    int heuristic;
} Node;

// Function to compare nodes by heuristic (lower is better)
int compare(const void *a, const void *b) {
    Node *n1 = (Node *)a;
    Node *n2 = (Node *)b;
    return n1->heuristic - n2->heuristic;
}

// Beam Search with History
void beamSearch(int graph[MAX][MAX], int n, int start, int goal, int heuristic[], int beam_width) {
    bool visited[MAX] = {false};
    Node frontier[MAX];
    int front_size = 0;

    // Start node
    frontier[front_size++] = (Node){start, heuristic[start]};
    visited[start] = true;

    printf("Beam Search Path: ");

    while (front_size > 0) {
        // Check if goal is in frontier
        for (int i = 0; i < front_size; i++) {
            if (frontier[i].node == goal) {
                printf("%d ", frontier[i].node);
                printf("\nGoal found!\n");
                return;
            }
        }

        // Expand all nodes in the frontier
        Node next_level[MAX];
        int next_size = 0;

        for (int i = 0; i < front_size; i++) {
            int curr = frontier[i].node;
            printf("%d ", curr);

            for (int j = 0; j < n; j++) {
                if (graph[curr][j] && !visited[j]) {
                    visited[j] = true;
                    next_level[next_size++] = (Node){j, heuristic[j]};
                }
            }
        }

        // Sort next level by heuristic
        qsort(next_level, next_size, sizeof(Node), compare);

        // Keep only beam_width best nodes
        front_size = (next_size < beam_width) ? next_size : beam_width;
        for (int i = 0; i < front_size; i++) {
            frontier[i] = next_level[i];
        }
    }

    printf("\nGoal not found.\n");
}

int main() {
    int n = 6; // Number of nodes
    int graph[MAX][MAX] = {
        // 0  1  2  3  4  5
        {0, 1, 1, 0, 0, 0}, // 0
        {1, 0, 0, 1, 1, 0}, // 1
        {1, 0, 0, 1, 0, 0}, // 2
        {0, 1, 1, 0, 0, 1}, // 3
        {0, 1, 0, 0, 0, 1}, // 4
        {0, 0, 0, 1, 1, 0}  // 5
    };

    int heuristic[MAX] = {7, 6, 5, 4, 3, 0}; // Lower means closer to goal

    int start = 0, goal = 5, beam_width = 2;

    beamSearch(graph, n, start, goal, heuristic, beam_width);

    return 0;
}