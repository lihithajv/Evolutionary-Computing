#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct {
    int node;
    int heuristic;
} Node;

int graph[MAX][MAX];
int visited[MAX];
int heuristic[MAX];
int n, beam_width;

void sortByHeuristic(Node arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[j].heuristic < arr[i].heuristic) {
                Node temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void beamSearch(int start, int goal) {
    Node currentLevel[MAX], nextLevel[MAX];
    int currentSize = 1, nextSize;
    
    currentLevel[0].node = start;
    currentLevel[0].heuristic = heuristic[start];
    visited[start] = 1;

    while (currentSize > 0) {
        // Print current level
        printf("Current Level: ");
        for (int i = 0; i < currentSize; i++)
            printf("%d ", currentLevel[i].node);
        printf("\n");

        // Check if goal found
        for (int i = 0; i < currentSize; i++) {
            if (currentLevel[i].node == goal) {
                printf("Goal %d found!\n", goal);
                return;
            }
        }

        // Prepare next level
        nextSize = 0;
        for (int i = 0; i < currentSize; i++) {
            int node = currentLevel[i].node;
            for (int j = 0; j < n; j++) {
                if (graph[node][j] && !visited[j]) {
                    visited[j] = 1;
                    nextLevel[nextSize].node = j;
                    nextLevel[nextSize].heuristic = heuristic[j];
                    nextSize++;
                }
            }
        }

        // Sort next level by heuristic
        sortByHeuristic(nextLevel, nextSize);

        // Keep only beam_width best nodes
        currentSize = (nextSize < beam_width) ? nextSize : beam_width;
        for (int i = 0; i < currentSize; i++) {
            currentLevel[i] = nextLevel[i];
        }
    }
    printf("Goal not found!\n");
}

int main() {
    int start, goal;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        printf("Heuristic for node %d: ", i);
        scanf("%d", &heuristic[i]);
    }

    printf("Enter start node: ");
    scanf("%d", &start);
    printf("Enter goal node: ");
    scanf("%d", &goal);
    printf("Enter beam width: ");
    scanf("%d", &beam_width);

    for (int i = 0; i < n; i++) visited[i] = 0;

    beamSearch(start, goal);

    return 0;
}
