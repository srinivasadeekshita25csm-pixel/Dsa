#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int n;

void bfs(int start) {
    int queue[MAX];
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("BFS Traversal: ");

    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);

        for (int i = 0; i < n; i++) {
            if (graph[vertex][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

void dfs(int vertex) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < n; i++) {
        if (graph[vertex][i] && !visited[i])
            dfs(i);
    }
}

int main(void) {
    int edges, u, v, start;

    printf("Enter number of vertices (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of vertices!\n");
        return 1;
    }

    printf("Enter number of edges: ");
    if (scanf("%d", &edges) != 1 ||
        edges < 0 || edges > n * (n - 1) / 2) {
        printf("Invalid number of edges!\n");
        return 1;
    }

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");

        if (scanf("%d%d", &u, &v) != 2 ||
            u < 0 || u >= n || v < 0 || v >= n || u == v) {
            printf("Invalid edge!\n");
            return 1;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("Enter starting vertex: ");
    if (scanf("%d", &start) != 1 ||
        start < 0 || start >= n) {
        printf("Invalid starting vertex!\n");
        return 1;
    }

    bfs(start);

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("DFS Traversal: ");
    dfs(start);
    printf("\n");

    return 0;
}