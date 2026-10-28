#include <stdio.h>

#define MAX 20
#define INF 99999

int main(void) {
    int cost[MAX][MAX];
    int n;

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

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (cost[i][k] != INF &&
                    cost[k][j] != INF &&
                    cost[i][k] <= INF - cost[k][j] &&
                    cost[i][k] + cost[k][j] < cost[i][j]) {
                    cost[i][j] = cost[i][k] + cost[k][j];
                }
            }
        }
    }

    printf("\nAll-Pairs Shortest Distance Matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (cost[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", cost[i][j]);
        }
        printf("\n");
    }

    return 0;
}
