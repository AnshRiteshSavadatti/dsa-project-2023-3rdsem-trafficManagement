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
        printf("%s \n", a[i].areaName);
    }
    printf("\n");
    return;
}

/*
void readGraphFromFile(int cost[MAX_VERTICES][MAX_VERTICES]) {
    fp = fopen("dijktrasNodes.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }
    while(!feof(fp)){
        int x,y,w;
        fscanf(fp, "%d %d %d", &x, &y, &w);
        cost[x][y] = w;
    }

    fclose(fp);
    return;
}
*/

void writeGraphToFile(int cost[MAX_VERTICES][MAX_VERTICES]) {
    fp = fopen("dijkstraNodes.txt", "w");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }

    for (int i = 0; i < MAX_VERTICES; ++i) {
        for (int j = i + 1; j < MAX_VERTICES; ++j) {
            if (cost[i][j] != 0) {
                fprintf(fp, "%d %d %d\n", i, j, cost[i][j]);
            }
        }
    }

    fclose(fp);
}


void generateRandomEdges(int cost[MAX_VERTICES][MAX_VERTICES]) {

    // Create a connected graph
    for (int i = 1; i < MAX_VERTICES; ++i) {
        int edge1 = i;
        int edge2 = rand() % i;  // Connect to a random node before the current one
        int weight = rand() % 10 + 1;  // Random weight between 1 and 10
        cost[edge1][edge2] = weight;
        cost[edge2][edge1] = weight;  // Assuming an undirected graph
    }
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

int loadThenodeNames(nodesNames a[], FILE* fp){
    int i = 0;
    fp = fopen("DijktrasNodesAreaRelation.txt", "r");
    if(fp == NULL){
        printf("Error in opeaning in dijktras.txt\n");
        return -1;
    }
    while(!feof(fp)){
        fscanf(fp,"%d %s",&a[i].index, &a[i].areaName);
        i++;
    }
    fclose(fp);
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