#include <stdio.h>
#include <limits.h>

#define MAX 10

void hillClimbing(int graph[MAX][MAX], int heuristic[MAX], int n, int start, int goal) {
    int current = start;
    int visited[MAX] = {0};

    printf("Path: %d ", current);
    visited[current] = 1;

    while (current != goal) {
        int next = -1;
        int minH = INT_MAX;

        // Look for the neighbor with the smallest heuristic value
        for (int i = 0; i < n; i++) {
            if (graph[current][i] != 0 && !visited[i]) {
                if (heuristic[i] < minH) {
                    minH = heuristic[i];
                    next = i;
                }
            }
        }

        // If no better neighbor found, stop
        if (next == -1 || heuristic[next] >= heuristic[current]) {
            printf("\nNo better neighbor found. Stopping.\n");
            break;
        }

        current = next;
        visited[current] = 1;
        printf("-> %d ", current);
    }

    if (current == goal) {
        printf("\nGoal %d reached!\n", goal);
    }
}

int main() {
    int n;
    int graph[MAX][MAX], heuristic[MAX];
    int start, goal;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &heuristic[i]);

    printf("Enter start node: ");
    scanf("%d", &start);

    printf("Enter goal node: ");
    scanf("%d", &goal);

    hillClimbing(graph, heuristic, n, start, goal);

    return 0;
}