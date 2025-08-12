#include <stdio.h>
#include <limits.h>

#define N 6 // S, A, B, C, D, G
#define INF 9999

// Node labels for readability
enum { S, A, B, C, D, G };

int min_cost = INT_MAX;
int best_path[100];
int best_len = 0;

void branchAndBound(int graph[N][N], int visited[N], int curr_node,
                    int goal, int cost_so_far, int path[], int level) {
    // If reached goal
    if (curr_node == goal) {
        if (cost_so_far < min_cost) {
            min_cost = cost_so_far;
            best_len = level;
            for (int i = 0; i < level; i++)
                best_path[i] = path[i];
        }
        return;
    }

    // Prune if cost already exceeds best
    if (cost_so_far >= min_cost)
        return;

    // Explore neighbors
    for (int i = 0; i < N; i++) {
        if (graph[curr_node][i] != INF && !visited[i]) {
            visited[i] = 1;
            path[level] = i;
            branchAndBound(graph, visited, i, goal,
                           cost_so_far + graph[curr_node][i], path, level + 1);
            visited[i] = 0;
        }
    }
}

int main() {
    // Example Graph (Adjacency Matrix)
    int graph[N][N] = {
        //  S     A     B     C     D     G
        {INF,   4,    2,  INF,  INF,  INF}, // S
        {INF, INF,  INF,    3,    6,  INF}, // A
        {INF,   5,  INF,  INF,    4,  INF}, // B
        {INF, INF,  INF,  INF,  INF,    7}, // C
        {INF, INF,  INF,  INF,  INF,    3}, // D
        {INF, INF,  INF,  INF,  INF,  INF}  // G
    };

    int visited[N] = {0};
    int path[100];

    visited[S] = 1; // Start at S
    path[0] = S;

    branchAndBound(graph, visited, S, G, 0, path, 1);

    printf("Minimum cost: %d\n", min_cost);
    printf("Path: ");
    for (int i = 0; i < best_len; i++) {
        switch (best_path[i]) {
            case S: printf("S "); break;
            case A: printf("A "); break;
            case B: printf("B "); break;
            case C: printf("C "); break;
            case D: printf("D "); break;
            case G: printf("G "); break;
        }
    }
    printf("\n");

    return 0;
}