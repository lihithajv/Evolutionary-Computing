#include <stdio.h>
#include <limits.h>

#define MAX 10

int graph[MAX][MAX];
int heuristic[MAX];
int visited[MAX];
int n;

// Function to find the best next node
int get_best_neighbor(int current) {
    int best = -1;
    int best_h = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (graph[current][i] != 0 && !visited[i]) { // If there's an edge & not visited
            if (heuristic[i] < best_h) { // Smaller heuristic is better
                best_h = heuristic[i];
                best = i;
            }
        }
    }
    return best;
}

void hill_climbing(int start) {
    int current = start;
    visited[current] = 1;
    printf("Start at node %d (h=%d)\n", current, heuristic[current]);

    while (1) {
        int next = get_best_neighbor(current);

        if (next == -1) {
            printf("No better neighbor found. Stopping at node %d (h=%d)\n", current, heuristic[current]);
            break;
        }

        if (heuristic[next] >= heuristic[current]) {
            printf("Reached a peak at node %d (h=%d)\n", current, heuristic[current]);
            break;
        }

        printf("Move to node %d (h=%d)\n", next, heuristic[next]);
        visited[next] = 1;
        current = next;
    }
}

int main() {
    int start;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix of the graph:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &heuristic[i]);
    }

    printf("Enter starting node: ");
    scanf("%d", &start);

    for (int i = 0; i < n; i++) visited[i] = 0;

    hill_climbing(start);

    return 0;
}