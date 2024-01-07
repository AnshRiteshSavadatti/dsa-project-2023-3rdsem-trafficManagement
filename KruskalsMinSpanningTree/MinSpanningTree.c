// Consider a city with a road network represented as a weighted undirected graph,
//  where each road is a weighted edge with the weight corresponding to the travel time. 
// The city's traffic control center wants to optimize traffic flow by identifying the 
// minimum spanning tree of the road network using Kruskal's algorithm.

#include<stdio.h>

typedef struct node{
    int u;
    int v;
    int w;
}NODE;

NODE edges[30];

// void input(NODE edges[], int n){
//     for(int i=0; i<n; i++){
//         scanf("%d%d%d",&edges[i].u, &edges[i].v, &edges[i].w);
//     }
//     return;
// }

// void sort(NODE edges[], int n){
//     for(int i=0; i<n-1; i++){
//         for(int j=0; j<n-1-i; j++){
//             if(edges[j].w > edges[j+1].w){
//                 NODE t = edges[j];
//                 edges[j] = edges[j+1];
//                 edges[j+1] = t;
//             }
//         }
//     }
//     return;
// }

void swap(NODE* a, NODE* b){
    NODE temp = *a;
    *a = *b;
    *b = temp;
    return;
}

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
            printf("%d %d\n",edges[i].u, edges[i].v);
        }
    }
    printf("\n");
    return sum;
}

void print(int arr[], int n){
    for(int i=0; i<n; i++){
        printf("%d\t",arr[i]);
    }
    return;
}


int main(){
    int n;
    printf("Enter the number of edges\n");
    scanf("%d",&n);
    // input(edges, n);

    // Reading input from file spanning.txt
    FILE* fp = fopen("spanning.txt", "r");
    int i =0;
    while(!feof(fp)){
        fscanf(fp, "%d %d %d",&edges[i].u, &edges[i].v, &edges[i].w);
        i++;
    }

    // closing the file 
    fclose(fp);

    // sorting on basis of weight
    quickSort(edges, 0, n);

    int arr[8];
    for(int i=0; i<8; i++){
        arr[i] = i;
    }

    // calling kruskal function
    printf("The edges are\n");
    int ans = kruskals(edges, n, arr);
    // print(arr, 8);
    printf("\nThe total weight is %d",ans);
    return 0;
}


// THE INPUT IS 
// 14
// 6 7 2
// 2 8 4
// 5 6 4
// 0 1 8
// 2 3 8 
// 6 8 17
// 2 3 14
// 7 8 14
// 0 7 16 
// 1 2 16
// 3 4 18
// 4 5 20
// 1 7 22
// 3 5 28 