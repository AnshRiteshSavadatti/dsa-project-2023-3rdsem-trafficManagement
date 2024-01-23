#include "header_file.h"
#include "constants.c"

// Function:    fillSpanningFile
// Description: Fills a file named "spanning.txt" with randomly generated integers.
// Input parameter: fp - file pointer
// return type: void
void fillSpanningFile(FILE * fp)
{
    fp = fopen("spanning.txt", "w");
    srand(time(NULL));

    for(int i=0; i<300; i++)
    {
        // rand()%100  rand()%100  rand()%1000
        fprintf(fp, "%d %d %d\n",rand()%100, rand()%100,rand()%1000);
    }
    fclose(fp);
    return;
}

// Function:    displayData
// Description: Displays node number and name from an array of Node structures.
// Input parameter: n - number of nodes, data - array of Node structures
// return type  void
void displayData(int n, Node data[])
{
    for(int i=0; i<n; i++)
    {
        printf("%d %s\n",data[i].n, data[i].name);
    }
    return;
}

// Function:    generate_random_string
// Description: Generates a random string of specified length.
// Input parameter: length - length of the random string
// return type: char* - pointer to the generated random string
char* generate_random_string(int length)
{
    // Seed the random number generator with the current time
    // Define the characters that can be used in the random string
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Allocate memory for the string, including space for the null terminator
    char* random_string = (char*)malloc((length + 1) * sizeof(char));
    // Generate random characters and build the string
    for (int i = 0; i < length; i++)
    {
        int index = rand() % (sizeof(charset) - 1);
        random_string[i] = charset[index];
    }

    // Add null terminator to the end of the string
    random_string[length] = '\0';
    return random_string;
}

// Function:    fillKruskalsFile
// Description: Fills a file named "kruskalsRepresentation.txt" with randomly generated node numbers and names.
// Input params: fp - file pointer
// return type: void
void fillKruskalsFile(FILE* fp)
{
    fp = fopen("kruskalsRepresentation.txt", "w");
    char *name;
    for(int i=0; i < 100; i++)
    {
        name = generate_random_string(10);
        fprintf(fp, "%d %s\n", i, name);
    }
    fclose(fp);
    return;
}

// Function:    readKruskals
// Description: Reads node numbers and names from a file named "kruskalsRepresentation.txt" into an array of Node structures.
// Input parameter: fp - file pointer, data - array of Node structures
// return type void
void readKruskals(FILE* fp, Node data[])
{
    fp = fopen("kruskalsRepresentation.txt","r");
    int j = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%d %s\n",&data[j].n, &data[j].name);
        j++;
    }
    return;
}

// Function:    swap
// Description: Swaps the positions of two NODE structures.
// Input params: a, b - pointers to NODE structures
void swap(NODE* a, NODE* b)
{
    NODE temp = *a;
    *a = *b;
    *b = temp;
    return;
}

// Function:    partition
// Description: Partitions the array using Tony's logic for quicksort
// Input parameters:
//   a[] - array of NODE elements to be partitioned
//   l   - left index of the partition
//   r   - right index of the partition
// Return type: int - the index of the pivot element after partitioning
int partition(NODE a[], int l, int r)
{
    NODE P = a[l];
    int i = l;
    int j = r+1;

    // Using tonys logic of partition in quick sort
    do
    {
        do
        {
            i++;
        }
        while(P.w > a[i].w);
        do
        {
            j--;
        }
        while(P.w < a[j].w);
        swap(&a[i], &a[j]);
    }
    while(i < j);

    swap(&a[i], &a[j]);
    swap(&a[l], &a[j]);

    return j;

}

// Function:    quickSort
// Description: Recursive function to perform quicksort on the array
// Input parameters:
//   edges[] - array of NODE elements to be sorted
//   l       - left index of the array/subarray
//   r       - right index of the array/subarray
// Return type: void
void quickSort(NODE edges[], int l, int r)
{
    if(l < r)
    {
        // we can sort
        int p = partition(edges, l, r);

        // calling Quick Sort on both the parts
        quickSort(edges, l, p-1);
        quickSort(edges, p+1, r);
    }
    return;
}

// Function:    find
// Description: Checks if two elements belong to the same set
// Input parameters:
//   arr[] - array representing disjoint sets
//   u     - element u
//   v     - element v
// Return type: int - 1 if u and v belong to the same set, 0 otherwise
int find(int arr[], int u, int v)
{
    if(arr[u] == arr[v])
        return 1;
    return 0;
}

// Function:    union_
// Description: Performs union operation on two sets represented by arr[]
// Input parameters:
//   arr[] - array representing disjoint sets
//   n     - size of the array
//   u     - element u
//   v     - element v
// Return type: void
void union_(int arr[], int n, int u, int v)
{
    int temp = arr[u];
    for(int i=0; i<n; i++)
    {
        if(arr[i] == temp)
            arr[i] = arr[v];
    }
    return;
}

// Function:    kruskals
// Description: Implements Kruskal's algorithm for finding minimum spanning tree
// Input parameters:
//   edges[] - array of NODE elements representing the graph edges
//   n       - number of vertices in the graph
//   arr[]   - array representing disjoint sets
// Return type: int - sum of weights of edges in the minimum spanning tree
int kruskals(NODE edges[], int n, int arr[])
{
    int sum = 0;
    for(int i=0; i<n; i++)
    {
        if(!find(arr, edges[i].u, edges[i].v))
        {
            union_(arr, 10, edges[i].u, edges[i].v);
            sum += edges[i].w;
            printf("%d %s  %d %s\n",edges[i].u,data[edges[i].u].name, edges[i].v,data[edges[i].v].name);
        }
    }
    printf("\n");
    return sum;
}
