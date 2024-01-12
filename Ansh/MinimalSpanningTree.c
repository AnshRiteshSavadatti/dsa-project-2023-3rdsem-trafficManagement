#include "header_file.h"
#include "constants.c"

// filling spanning file
void fillSpanningFile(FILE * fp){
    fp = fopen("spanning.txt", "w");
    srand(time(NULL));

    for(int i=0; i<300; i++){
        // rand()%100  rand()%100  rand()%1000
        fprintf(fp, "%d %d %d\n",rand()%100, rand()%100,rand()%1000);
    }
    fclose(fp);
    return;
}

// displaying the node and name relation
void displayData(int n, Node data[]){
    for(int i=0; i<n; i++){
        printf("%d %s\n",data[i].n, data[i].name);
    }
    return;
}

char* generate_random_string(int length) {
    // Seed the random number generator with the current time
    // Define the characters that can be used in the random string
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Allocate memory for the string, including space for the null terminator
    char* random_string = (char*)malloc((length + 1) * sizeof(char));
    // Generate random characters and build the string
    for (int i = 0; i < length; i++) {
        int index = rand() % (sizeof(charset) - 1);
        random_string[i] = charset[index];
    }

    // Add null terminator to the end of the string
    random_string[length] = '\0';
    return random_string;
}

// fill the file
void fillKruskalsFile(FILE* fp){
    fp = fopen("kruskalsRepresentation.txt", "w");
    char *name;
    for(int i=0; i < 100; i++){
        name = generate_random_string(10);
        fprintf(fp, "%d %s\n", i, name);
    }
    fclose(fp);
    return;
}

// read file
void readKruskals(FILE* fp, Node data[]){
    fp = fopen("kruskalsRepresentation.txt","r");
    int j = 0;
    while(!feof(fp)){
        fscanf(fp,"%d %s\n",&data[j].n, &data[j].name);
        j++;
    }
    return;
}
// function to swap the two nodes
void swap(NODE* a, NODE* b){
    NODE temp = *a;
    *a = *b;
    *b = temp;
    return;
}

// partition function in quick-sort
int partition(NODE a[], int l, int r){
    NODE P = a[l];
    int i = l;
    int j = r+1;

    // Using tonys logic of partition in quick sort
    do{
        do{
            i++;
        }while(P.w > a[i].w);
        do{
            j--;
        }while(P.w < a[j].w);
        swap(&a[i], &a[j]);
    }while(i < j);

    swap(&a[i], &a[j]);
    swap(&a[l] , &a[j]);

    return j;

}

// calling quicksort algorithm
void quickSort(NODE edges[], int l, int r){
    if(l < r){
        // we can sort
        int p = partition(edges, l, r);

        // calling Quick Sort on both the parts
        quickSort(edges, l, p-1);
        quickSort(edges, p+1, r);
    }
    return;
}

int find(int arr[], int u, int v){
    if(arr[u] == arr[v])
        return 1;
    return 0;
}

void union_(int arr[], int n, int u, int v){
    int temp = arr[u];
    for(int i=0; i<n; i++){
        if(arr[i] == temp)
            arr[i] = arr[v];
    }
    return;
}

int kruskals(NODE edges[], int n, int arr[]){
    int sum = 0;
    for(int i=0; i<n; i++){
        if(!find(arr, edges[i].u, edges[i].v)){
            union_(arr, 10, edges[i].u, edges[i].v);
            sum += edges[i].w;
            printf("%d %s  %d %s\n",edges[i].u,data[edges[i].u].name, edges[i].v,data[edges[i].v].name);
        }
    }
    printf("\n");
    return sum;
}
