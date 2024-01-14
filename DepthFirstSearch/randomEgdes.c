#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 100

void generateAndWriteRandomEdges() {
    srand(time(NULL));

    FILE *fp = fopen("DFS_Edges.txt", "w");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }

    // Create a connected graph and write edges to file simultaneously
    for (int i = 1; i < MAX_VERTICES; ++i) {
        int edge1 = i;
        int edge2 = rand() % i;  // Connect to a random node before the current one
        int weight = rand() % 10 + 1;  // Random weight between 1 and 10

        fprintf(fp, "%d %d %d\n", edge1, edge2, weight);
        fprintf(fp, "%d %d %d\n", edge2, edge1, weight);  // Assuming an undirected graph
    }

    fclose(fp);
}

int main() {
    generateAndWriteRandomEdges();

    return 0;
}
