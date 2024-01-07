// A city has a road network represented as an undirected graph, where each road is a connection between two intersections. 
// The intersections are labeled with unique identifiers. The city's traffic management department is interested in optimizing
//  traffic flow and wants to perform a Depth-First Search (DFS) to analyze the connected components of the road network.

#include<stdio.h>
#include<stdlib.h>

int visited[10] = {0};

void dfs(int m[10][10], int v, int source){
    visited[source] = 1;
    for(int i=0; i<v; i++){
        if(m[source][i] == 1 && visited[i] == 0){
            printf("%d\t",i);
            dfs(m, v, i);
        }
    }
    return;
}


int main(){
    int v = 5;
    int m[10][10];
    // int m[10][10] = {{0,1,1,0,0}, {1,0,0,1,1},{1,0,0,0,1}, {0,1,0,0,0}, {0,1,1,0,0}};
    int source;
    printf("Enter the source\n");
    scanf("%d",&source);

    // assiging the matix value with 0
    for(int i=0; i<v; i++){
        for(int j=0; j<v; j++){
            m[i][j] = 0;
        }
    }

    // checking if source is valid
    if(source < 0 || source > v ){
        printf("Invalid Input\n");
        return -1;
    }
 
    // taking input from file
    FILE * fp = fopen("dfs.txt", "r");
    
    // reading the file 
    while(!feof(fp)){
        int x,y;
        fscanf(fp,"%d %d ",&x, &y);
        fscanf(fp, "%d", &m[x][y]);
    }
    fclose(fp);

    printf("The dfs travels is \n");
    printf("%d\t",source);
    dfs(m, v, source);
    
    
    return 0;
    
}