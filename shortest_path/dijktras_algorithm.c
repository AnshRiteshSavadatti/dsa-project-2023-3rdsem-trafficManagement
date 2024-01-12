#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <limits.h>

#define MAX_VERTICES 20

int distance[MAX_VERTICES];
int path[MAX_VERTICES];
int visited[MAX_VERTICES];

// creating a structure for storing index {node} and areaName to implement dijktras

typedef struct nodesNames{
    int index;
    char areaName[50];
}nodesNames;

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

void print(int v, nodesNames a[]) {
    printf("\nThe distance array is\n");
    for (int i = 0; i < v; i++) {
        printf("%d ", distance[i]);
        printf("%s \n", a[path[i]].areaName);
    }
    // printf("\n");
    // printf("The path array is\n");
    // for (int i = 0; i < v; i++) {
    //     printf("%d ", path[i]);
    // }    
    printf("\n");
    return;
}

void readGraphFromFile(int cost[MAX_VERTICES][MAX_VERTICES], int v) {
    FILE *file = fopen("spanning.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    while(!feof(file)){
        int x,y,w;
        fscanf(file, "%d %d %d", &x, &y, &w);
        cost[x][y] = w;
    }

    fclose(file);
    return;
}

void assignCostMatrixValue(int m[][MAX_VERTICES]){
    for(int i= 0; i<MAX_VERTICES; i++){
        for(int j = 0; j < MAX_VERTICES; j++){
            m[i][j] = 9999;
        }
        m[i][i] = 0;
    }
    return;
}

int loadThenodeNames(nodesNames a[]){
    int i = 0;
    FILE* fp = fopen("Dijktras.txt", "r");
    while(!feof(fp)){
        fscanf(fp,"%d %s",&a[i].index, &a[i].areaName);
        i++;
    }
    return i;
}

int BruteForceStringMatch(char t[], char p[], int n, int m){
    for(int i = 0; i < n; i++){
        if(t[i] != p[i]){
            return 0;
        }
    }
    return 1;
}

int findSource(char source[], nodesNames a[], int v){
    for(int i =0; i < v; i++){
        if(strlen(source) == strlen(a[i].areaName)){
            if(BruteForceStringMatch(source, a[i].areaName, strlen(source), strlen(a[i].areaName))){
                return i;
            }
        }
    }
    return -1;
}

void printAreaNames(int n, nodesNames a[]){

    for(int i=0; i<n; i++){
        printf("%s\n",a[i].areaName);
    }
    return;
}



int main() {
    int v;
    printf("Enter the number of vertices\n");
    scanf("%d", &v);

    // allocating memory for nodeNames structure in the form of array
    nodesNames* area = (nodesNames*) malloc (v * sizeof(nodesNames));

    // nodesNames area[50];
    int cost[MAX_VERTICES][MAX_VERTICES];
    assignCostMatrixValue(cost);
    printf("Cost matrix assigned\n");
    
    // reading the weights of graph from file
    readGraphFromFile(cost, v);
   

    // loading the names of places on file with respective nodes
    int n = loadThenodeNames(area);
     printf("Reading from file completed\n");
    // int src;

    char source[50];
    printf("Enter the source among these\n");
    printAreaNames(n,area);
    printf("Enter the source\n");
    scanf("%s", &source);
    int src = findSource(source, area, v);
    printf("finding the source completed\n");

    if(src == -1){
        printf("Print valid source\n");
        return -1;
    }

    for (int i = 0; i < v; i++) {
        distance[i] = cost[src][i];
    }
    for (int i = 0; i < v; i++) {
        path[i] = src;
    }

    dijkstras(cost, v, src);
    print(v, area);

    return 0;
}


// implementing a string search algorithm
// taking areas as input
// creating extra nodes for each for saving name
// google maps for names and decide a graph
