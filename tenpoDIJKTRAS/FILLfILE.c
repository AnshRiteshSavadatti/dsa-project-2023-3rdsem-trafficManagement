#include<stdio.h>

struct node{
    char name[50];
}node[100];

int main(){
    FILE* fp;
    fp = fopen("DijktrasNodesAreaRelation.txt", "r");
    
    int i=0;
    while(!feof(fp)){
        fscanf(fp, "%s", &node[i].name);
        i++;
    }
    fclose(fp);
    fp = fopen("DijktrasNodesAreaRelation.txt", "w");
    for(int i=0; i<100; i++){
        fprintf(fp, "%d %s\n",i, node[i].name);
    }
    return 0;
}