#include <stdio.h>

#define MAX 20
#define INF 99999

int main(void) {
    int cost[MAX][MAX];
    int distance[MAX];
    int visited[MAX] = {0};
    int n, source;

    printf("Enter number of vertices (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of vertices!\n");
        return 1;
    }

    printf("Enter cost matrix (use %d for no edge):\n", INF);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &cost[i][j]) != 1 ||
                cost[i][j] < 0 || cost[i][j] > INF) {
                printf("Invalid matrix value!\n");
                return 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (cost[i][i] != 0) {
            printf("Diagonal entries must be zero!\n");
            return 1;
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);

    if (scanf("%d", &source) != 1 ||
        source < 0 || source >= n) {
        printf("Invalid source vertex!\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        distance[i] = INF;

    distance[source] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        int minimum = INF;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && distance[i] < minimum) {
                minimum = distance[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] &&
                cost[u][v] != INF &&
                distance[u] != INF &&
                distance[u] <= INF - cost[u][v] &&
                distance[u] + cost[u][v] < distance[v]) {
                distance[v] = distance[u] + cost[u][v];
            }
        }
    }

    printf("\nShortest distances from vertex %d:\n", source);
    printf("Vertex\tDistance\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t", i);

        if (distance[i] == INF)
            printf("Unreachable\n");
        else
            printf("%d\n", distance[i]);
    }

    return 0;
}