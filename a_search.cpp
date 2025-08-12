#include <stdio.h>
#include <limits.h>

#define N 6 // S, A, B, C, D, G
#define INF 9999

// Node names for readability
enum { S, A, B, C, D, G };

// Function to find the node with the lowest f-score
int getLowestF(int openSet[], int fScore[], int n) {
    int min = INF, index = -1;
    for (int i = 0; i < n; i++) {
        if (openSet[i] && fScore[i] < min) {
            min = fScore[i];
            index = i;
        }
    }
    return index;
}

void reconstructPath(int cameFrom[], int current) {
    if (cameFrom[current] != -1) {
        reconstructPath(cameFrom, cameFrom[current]);
    }
    switch (current) {
        case S: printf("S "); break;
        case A: printf("A "); break;
        case B: printf("B "); break;
        case C: printf("C "); break;
        case D: printf("D "); break;
        case G: printf("G "); break;
    }
}

void aStar(int graph[N][N], int start, int goal, int heuristic[]) {
    int openSet[N] = {0};
    int closedSet[N] = {0};
    int cameFrom[N];

    int gScore[N];
    int fScore[N];

    for (int i = 0; i < N; i++) {
        gScore[i] = INF;
        fScore[i] = INF;
        cameFrom[i] = -1;
    }

    gScore[start] = 0;
    fScore[start] = heuristic[start];
    openSet[start] = 1;

    while (1) {
        int current = getLowestF(openSet, fScore, N);
        if (current == -1) break; // No path
        if (current == goal) {
            printf("Shortest path: ");
            reconstructPath(cameFrom, current);
            printf("\nTotal cost: %d\n", gScore[goal]);
            return;
        }

        openSet[current] = 0;
        closedSet[current] = 1;

        for (int neighbor = 0; neighbor < N; neighbor++) {
            if (graph[current][neighbor] != INF && !closedSet[neighbor]) {
                int tentative_gScore = gScore[current] + graph[current][neighbor];
                if (!openSet[neighbor]) openSet[neighbor] = 1;

                if (tentative_gScore < gScore[neighbor]) {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentative_gScore;
                    fScore[neighbor] = gScore[neighbor] + heuristic[neighbor];
                }
            }
        }
    }

    printf("No path found.\n");
}

int main() {
    // Graph adjacency matrix
    int graph[N][N] = {
        //  S     A     B     C     D     G
        {INF,   4,    2,  INF,  INF,  INF}, // S
        {INF, INF,  INF,    3,    6,  INF}, // A
        {INF,   5,  INF,  INF,    4,  INF}, // B
        {INF, INF,  INF,  INF,  INF,    7}, // C
        {INF, INF,  INF,  INF,  INF,    3}, // D
        {INF, INF,  INF,  INF,  INF,  INF}  // G
    };

    // Heuristic values (estimated cost to reach G)
    int heuristic[N] = {7, 6, 4, 7, 3, 0}; // Example values

    aStar(graph, S, G, heuristic);

    return 0;
}