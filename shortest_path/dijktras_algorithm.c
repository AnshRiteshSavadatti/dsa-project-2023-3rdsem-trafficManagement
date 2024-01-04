#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 10

int distance[MAX_VERTICES];
int path[MAX_VERTICES];
int visited[MAX_VERTICES];

void dijkstras(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src) {
    int j;
    visited[src] = 1;
    for (j = 0; j < v - 1; j++) {
        int min = INT_MAX;
        int u = 0;
        for (int i = 0; i < v; i++) {
            if (visited[i] == 0 && distance[i] < min) {
                min = distance[i];
                u = i;
            }
        }
        visited[u] = 1;
        for (int i = 0; i < v; i++) {
            if (visited[i] == 0 && distance[i] > cost[u][i] + distance[u]) {
                distance[i] = cost[u][i] + distance[u];
                path[i] = u;
            }
        }
    }
    return;
}

void print(int v) {
    printf("\nThe distance array is\n");
    for (int i = 0; i < v; i++) {
        printf("%d ", distance[i]);
    }
    printf("\n");
    printf("The path array is\n");
    for (int i = 0; i < v; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
    return;
}

void readGraphFromFile(int cost[MAX_VERTICES][MAX_VERTICES], int v) {
    FILE *file = fopen("cost_file.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    // while(!feof(file)){
    //     int x,y;
    //     fscanf(file, "%d%d", &x, &y);
    //     fscanf(file, "%d", &cost[x][y]);
    // }
    int x, y, w;
    while (fscanf(file, "%d%d%d", &x, &y, &w) == 3) {
        cost[x][y] = w;
    }

    fclose(file);
    return;
}

int main() {
    int v;
    // 3 hai file mai
    printf("Enter the number of vertices\n");
    scanf("%d", &v);

    int cost[MAX_VERTICES][MAX_VERTICES];
    for(int i= 0; i<MAX_VERTICES; i++){
        for(int j = 0; j < MAX_VERTICES; j++){
            cost[i][j] = 9999;
        }
    }
    readGraphFromFile(cost, v);

    int src;
    printf("Enter the source\n");
    scanf("%d", &src);

    for (int i = 0; i < v; i++) {
        distance[i] = cost[src][i];
    }
    for (int i = 0; i < v; i++) {
        path[i] = src;
    }

    dijkstras(cost, v, src);
    print(v);

    return 0;
}