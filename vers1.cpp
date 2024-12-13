//добавить начальный экран, кто делал, какая тема
//Добавить пункт 5.1 чтобы изменить граф на эйлеров,
//пункт 6 изменить чтобы было сохранение результата самого обхода.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
int** createG1(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            G[i][j] = rand() % 2;
            if (i == j) {
                G[i][j] = 0;
            }
        }
    }
    return G;
}
int** createG2(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            G[i][j]= G[j][i] = rand() % 2;
            if (i == j) {
                G[i][j] = 0;
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
void dfs(int v, int* visited, int** graph, int n) {
    visited[v] = 1; // Помечаем вершину как посещенную
    for (int u = 0; u < n; u++) {
        if (graph[v][u] == 1 && !visited[u]) {
            dfs(u, visited, graph, n);
        }
    }
}
int main() {
    setlocale(LC_ALL, "Rus");
    int n = 5, start, search = 1;
    int* degree = (int*)malloc(n * sizeof(int));
    int** graph = NULL;
    while (search != 0) {
        printf("0.Выход\n");
        printf("1.Сгенерировать ориентированную матрицу\n");
        printf("2.Сгенерировать неориентированную матрицу\n");
        printf("3.Ввести матрицу из файла\n");
        printf("4.Ввести матрицу вручную\n");
        printf("5.Обход\n");
        printf("6.Сохранить матрицу в файл\n");
        printf("Выберите пункт меню:\n");
        scanf_s("%d", &search);
        switch (search) {
        case 0: {
            printf("До свидания! Я рассчитываю на оценку 5! \n");
            break;
        }
        case 1: {
            printf("Ориентированная матрица\n");
            printf("Введите размер матрицы: \n");
            scanf_s("%d", &n);
            graph = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++) {
                graph[i] = (int*)malloc(n * sizeof(int));
            }
            graph = createG1(n);
            printG(graph, n);
            break;
        }
        case 2: {
            printf("Неориентированная матрица\n");
            printf("Введите размер матрицы: \n");
            scanf_s("%d", &n);
            graph = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++) {
                graph[i] = (int*)malloc(n * sizeof(int));
            }
            graph = createG2(n);
            printG(graph, n);
            break;
        }
        case 3: {
            printf("Введите название файла из которого надо загрузить матрицу:\n");
            char filename[100];
            scanf_s("%s", filename, (unsigned)_countof(filename));
            FILE* file;
            fopen_s(&file, filename, "r");
            if (file == NULL) {
                printf("Ошибка: не удалось открыть файл.\n");
                break;
            }
            fscanf_s(file, "%d", &n);

            graph = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++) {
                graph[i] = (int*)malloc(n * sizeof(int));
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    fscanf_s(file, "%d", &graph[i][j]);
                }
            }

            fclose(file);
            printG(graph, n);
            break;
        }
        case 4: {
            int timevar;
            printf("Введите размер матрицы\n");
            scanf_s("%d", &n);
            graph = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++) {
                graph[i] = (int*)malloc(n * sizeof(int));
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("Введите 1/0 для G[%d][%d]\n", i, j);
                    scanf_s("%d", &timevar);
                    if (timevar == 1 || timevar == 0) {
                        graph[i][j] = timevar;
                    }
                    else {
                        printf("error(1/0)\n");
                        if (i != 0 && j != 0) {
                            i = 0;
                            j = -1;
                        }
                        else if (i != 0 && j == 0) {
                            i = 0;
                        }
                        else if (i == 0 && j != 0) {
                            j = -1;
                        }
                        else if (i == 0 && j == 0) {
                            i = 0;
                            j = -1;
                        }
                    }
                }
            }
            printG(graph, n);
            break;
        }
        case 5: {
            int* visited = (int*)malloc(n * sizeof(int*));

            printf("Введите номер вершины, с которой начнется обход (1-%d): \n", n);
            scanf_s("%d", &start);
            start = start - 1;

            // Проверка, что все вершины имеют четные степени
            int isEulerian = 1; // Флаг для проверки, является ли граф Эйлеровым
            for (int i = 0; i < n; i++) {
                degree[i] = 0; // Инициализация массива степеней
                for (int j = 0; j < n; j++) {
                    degree[i] += graph[i][j]; // Вычисление степени вершины i
                }
                if (degree[i] % 2 != 0) {
                    isEulerian = 0; // Если у любой вершины нечетная степень
                    printf("Нечетная степень");
                    break;
                }
            }

            // Проверка, что граф связный
            if (isEulerian) {
                for (int i = 0; i < n; i++) {
                    visited[i] = 0;
                }
                dfs(start, visited, graph, n); // Начинаем DFS с заданной стартовой вершины
                // Проверка, что все вершины с ненулевой степенью были посещены
                for (int i = 0; i < n; i++) {
                    if (degree[i] > 0 && !visited[i]) {
                        isEulerian = 0; // Если любая вершина с ребрами не была посещена
                        break;
                    }
                }
            }

            // Если граф Эйлеров, выполняем обход Эйлера
            if (isEulerian) {
                printf("Эйлеров цикл:\n");
                Euler(graph, start, n, degree);
            }
            else {
                printf("Граф не имеет Эйлерова цикла.\n");
            }
            break;
        }
        case 6: {
            if (graph == NULL) {
                printf("Ошибка: матрица не существует. Сначала создайте или загрузите матрицу.\n");
                break;
            }

            printf("Введите название файла для сохранения матрицы:\n");
            char filename[100];
            scanf_s("%s", filename, (unsigned)_countof(filename));

            FILE* file;
            fopen_s(&file, filename, "w");
            if (file == NULL) {
                printf("Ошибка: не удалось открыть файл для записи.\n");
                break;
            }
            fprintf(file, "%d\n", n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    fprintf(file, "%d ", graph[i][j]);
                }
                fprintf(file, "\n");
            }

            fclose(file);
            printf("Матрица успешно сохранена в файл '%s'.\n", filename);
            break;
        }
        default: {
            printf("Неправильный выбор:\n");
            break;
        }
        }
    }
    return 0;
}