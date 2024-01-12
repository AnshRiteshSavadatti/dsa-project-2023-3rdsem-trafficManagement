#include <stdio.h>
#include <stdlib.h>

void printMatrix(int** matrix, int V) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void pruneEdges(int** matrix, int V, int src, int closedRoad) {
    matrix[src][closedRoad] = 0;
    matrix[closedRoad][src] = 0;
}

void updateToFile(int** matrix, int V, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int edgeCount = 0;
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (matrix[i][j] == 1) {
                edgeCount++;
            }
        }
    }

    fprintf(file, "%d %d\n", V, edgeCount);

    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (matrix[i][j] == 1) {
                fprintf(file, "%d %d\n", i, j);
            }
        }
    }

    fclose(file);
}

int main() {
    const char* filename = "road_update.txt";

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int V, E; // Number of vertices and edges
    fscanf(file, "%d %d", &V, &E);

    int** matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; ++i) {
        matrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; ++j) {
            matrix[i][j] = 0;
        }
    }

    int src, dest;
    for (int i = 0; i < E; ++i) {
        fscanf(file, "%d %d", &src, &dest);
        matrix[src][dest] = 1;
        matrix[dest][src] = 1;
    }

    fclose(file);

    printf("Original Matrix:\n");
    printMatrix(matrix, V);

    int closedRoad, sourceVertex;
    printf("Enter the closed road: ");
    scanf("%d", &closedRoad);

    printf("Enter the source vertex for pruning: ");
    scanf("%d", &sourceVertex);

    pruneEdges(matrix, V, sourceVertex, closedRoad);

    printf("\nMatrix after pruning road %d from vertex %d:\n", closedRoad, sourceVertex);
    printMatrix(matrix, V);

    updateToFile(matrix, V, filename);

    // Free allocated memory
    for (int i = 0; i < V; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
