#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                G[i][j] = G[j][i] = 1;
            }
        }
    }
    return G;
}

void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    return;
}

void Euler(int** graph, int v, int n, int* degree) {
    for (int u = 0; u < n; u++) {
        if (graph[v][u] == 1) {
            printf("Перешли из вершины %d в вершину %d\n", v + 1, u + 1);
            graph[v][u] = graph[u][v] = 0;
            degree[v]--;
            degree[u]--;
            printG(graph, n);
            Euler(graph, u, n, degree);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int n, start;

    printf("Введите размер вершины: ");
    scanf_s("%d", &n);
    int** graph = createG(n);
    int* degree = (int*)malloc(n * sizeof(int));

    printG(graph, n);

    printf("Введите номер вершины, с которой начнется обход (1-%d): ", n);
    scanf_s("%d", &start);
    start = start - 1;
    // проверка
    printf("Эйлеров цикл:\n");
    Euler(graph, start, n, degree);
    return 0;
}