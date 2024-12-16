//добавить начальный экран, кто делал, какая тема+
//Добавить пункт 6 чтобы изменить граф на эйлеров,+
//пункт 7 изменить чтобы было сохранение результата самого обхода.+
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
            G[i][j] = G[j][i] = rand() % 2;
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
void Euler(int** graph, int v, int n, int* degree, int* result, int* index) {
    for (int u = 0; u < n; u++) {
        if (graph[v][u] == 1) {
            graph[v][u] = graph[u][v] = 0;
            degree[v]--;
            degree[u]--;
            Euler(graph, u, n, degree, result, index);
        }
    }
    result[(*index)++] = v + 1; // Сохраняем вершину в результат
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
    printf("Курсовая работа\nПо дисциплине ЛиОАВИЗ\nНа тему: Реализация Эйлерова цикла\nВыполнил студент 23ВВВ2: Герасимов В. Р.\nПриняла: Юрова О. В.\n\n");
    system("PAUSE");
    system("cls");
    int n = 5, start, search = 1;
    int* degree = (int*)malloc(n * sizeof(int));
    int** graph = NULL;
    int** graph2 = NULL;
    int* result = (int*)malloc(n * n * sizeof(int)); // Массив для хранения результата обхода
    int index = 0; // Индекс для записи в массив результата
    while (search != 0) {
        printf("0.Выход\n");
        printf("1.Сгенерировать ориентированную матрицу\n");
        printf("2.Сгенерировать неориентированную матрицу\n");
        printf("3.Ввести матрицу из файла\n");
        printf("4.Ввести матрицу вручную\n");
        printf("5.Обход\n");
        printf("6.Изменить матрицу\n");
        printf("7.Сохранить результат в файл\n");
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
            if(n<0){
                printf("Недопустимый размер\n");
                break;
            }
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
            if (n < 0) {
                printf("Недопустимый размер\n");
                break;
            }
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
            if (n < 0) {
                printf("Недопустимый размер\n");
                    break;
            }
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
                        printf("Ошибка, введите предложенные символы (1/0)\n");
                        i = 0;
                        j = -1;
   
                    }
                }
            }
            printG(graph, n);
            break;
        }
        case 5: {
            if (graph == NULL) {
                printf("Ошибка: матрица не существует. Сначала создайте или загрузите матрицу.\n");
                break;
            }
            int* visited = (int*)malloc(n * sizeof(int));
            graph2 = (int**)malloc(n * sizeof(int*));
            for (int i = 0; i < n; i++) {
                graph2[i] = (int*)malloc(n * sizeof(int));
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    graph2[i][j] = graph[i][j];
                }
            }
            printf("Введите номер вершины, с которой начнется обход (1-%d): \n", n);
            scanf_s("%d", &start);
            if (start > n) {
                printf("Неправильный номер вершины\n");
                break;
            }
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
                    printf("Нечетная степень\n");
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
                        printf("Вершина не была посещена\n");
                        isEulerian = 0; // Если любая вершина с ребрами не была посещена
                        break;
                    }
                    else if (degree[i] == 0) {
                        printf("Нулевая степень\n");
                        isEulerian = 0; // Если у вершины нулевая степень, значит если мы в нее попадем,то выйти не сможем.
                        break;
                    }
                }
            }

            // Если граф Эйлеров, выполняем обход Эйлера
            if (isEulerian) {
                printf("Эйлеров цикл:\n");
                Euler(graph, start, n, degree, result, &index);
                for (int i = index - 1; i >= 0; i--) { // Выводим результат в обратном порядке
                    printf("%d ", result[i]);
                }
                printf("\n");
            }
            else {
                printf("Граф не имеет Эйлерова цикла.\n");
            }

            free(visited);

            break;
        }
        case 6: {
            if (graph == NULL) {
                printf("Ошибка: матрица не существует. Сначала создайте или загрузите матрицу.\n");
                break;
            }

            int v1, v2;
            printf("Текущая матрица смежности:\n");
            printG(graph, n);

            printf("Введите номера двух вершин (1-%d), между которыми нужно изменить ребро (добавить или удалить):\n", n);
            printf("Введите первую вершину: ");
            scanf_s("%d", &v1);
            printf("Введите вторую вершину: ");
            scanf_s("%d", &v2);

            // Преобразуем номера вершин в индексы массива
            v1 -= 1;
            v2 -= 1;

            // Проверяем корректность ввода
            if (v1 < 0 || v1 >= n || v2 < 0 || v2 >= n) {
                printf("Ошибка: некорректные номера вершин.\n");
                break;
            }

            // Изменяем ребро: если оно есть, удаляем; если его нет, добавляем
            if (graph[v1][v2] == 1) {
                graph[v1][v2] = 0;
                graph[v2][v1] = 0;
                printf("Ребро между вершинами %d и %d удалено.\n", v1 + 1, v2 + 1);
            }
            else {
                graph[v1][v2] = 1;
                graph[v2][v1] = 1;
                printf("Ребро между вершинами %d и %d добавлено.\n", v1 + 1, v2 + 1);
            }

            // Пересчитываем степени вершин
            for (int i = 0; i < n; i++) {
                degree[i] = 0;
                for (int j = 0; j < n; j++) {
                    degree[i] += graph[i][j];
                }
            }

            // Выводим обновлённую матрицу смежности
            printf("Обновлённая матрица смежности:\n");
            printG(graph, n);

            // Проверяем, стали ли все степени чётными
            int isEulerian = 1;
            for (int i = 0; i < n; i++) {
                if (degree[i] % 2 != 0) {
                    isEulerian = 0;
                    printf("Вершина %d имеет нечётную степень: %d\n", i + 1, degree[i]);
                }
            }

            if (isEulerian) {
                printf("Теперь граф может быть Эйлеровым. Все вершины имеют чётные степени.\n");
            }
            else {
                printf("Граф всё ещё не является Эйлеровым. Исправьте степени вершин.\n");
            }

            break;
        }
        case 7: {
            if (graph == NULL) {
                printf("Ошибка: матрица не существует. Сначала создайте или загрузите матрицу.\n");
                break;
            }
            printf("Введите название файла для сохранения матрицы и результата обхода:\n");
            char filename[100];
            scanf_s("%s", filename, (unsigned)_countof(filename));
            FILE* file;
            fopen_s(&file, filename, "w");
            if (file == NULL) {
                printf("Ошибка: не удалось открыть файл для записи.\n");
                break;
            }

            // Сохраняем размер матрицы
            fprintf(file, "Размер матрицы: %d\n", n);

            // Сохраняем матрицу
            fprintf(file, "Матрица:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    fprintf(file, "%d ", graph2[i][j]);
                }
                fprintf(file, "\n");
            }
            if (result == NULL) {
                printf("Ошибка: не был совершен обход.\n");
                break;
            }
            // Сохраняем результат обхода
            fprintf(file, "Результат обхода:\n");
            for (int i = index - 1; i >= 0; i--) { // Записываем результат в обратном порядке
                fprintf(file, "%d ", result[i]);
            }
            fprintf(file, "\n");

            fclose(file);
            printf("Матрица и результат обхода успешно сохранены в файл '%s'.\n", filename);
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