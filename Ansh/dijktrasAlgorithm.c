#include "header_file.h"
#include "constants.c"

// Function: heapify
// Description: Maintains the heap property of the array
// Input parameters: h - array, n - size of the array
// Return type: void
void heapify(int h[], int n)
{
    for (int i = n / 2; i >= 0; i--)
    {
        int k = i;
        int v = h[i];
        bool heap = false;
        while (!heap && k * 2 <= n)
        {
            int j = k * 2;
            if (j < n)
            {
                if (h[j] > h[j + 1])
                {
                    j = j + 1;
                }
            }
            if (v <= h[j])
            {
                heap = true;
            }
            else
            {
                h[k] = h[j];
                k = j;
            }
        }
        h[k] = v;
    }
    return;
}

// Function: deleteMin
// Description: Deletes the minimum element (root) from the heap
// Input parameters: arr - array, n - size of the array
// Return type: int - the deleted minimum element
int deleteMin(int arr[], int* n)
{
    if (*n <= 0)
    {
        printf("Heap is empty\n");
        return -1;
    }
    else
    {
        heapify(arr, *n);
        int r = arr[1];
        arr[1] = arr[*n];
        (*n)--;
        heapify(arr, *n);
        return r;
    }
}

// Function: dijkstras
// Description: Applies Dijkstra's algorithm to find the shortest paths from a source node
// Input parameters: cost - adjacency matrix, v - number of vertices, src - source vertex
// Return type: void
void dijkstras(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src)
{
    int j;
    visited[src] = 1;

    int* arr = (int*)malloc(MAX_VERTICES * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    for (j = 0; j < v - 1; j++)
    {
        int u = 0;
        int c = 0;
        for (int i = 0; i < v; i++)
        {
            if (visited[i] == 0)
            {
                arr[++c] = distance[i];
            }
        }
        u = deleteMin(arr, &c);
        int index;
        if (u != -1)
        {
            for (int i = 0; i < v; i++)
            {
                if (visited[i] == 0 && distance[i] == u)
                {
                    index = i;
                }
            }
            visited[index] = 1;
            for (int i = 0; i < v; i++)
            {
                if (visited[i] == 0 && distance[i] > cost[index][i] + distance[index])
                {
                    distance[i] = cost[index][i] + distance[index];
                    path[i] = index;
                }
            }
        }
    }

    free(arr);
    return;
}

// Function: print
// Description: Prints the distance array along with corresponding area names
// Input parameters: v - number of vertices, a - array of nodesNames
// Return type: void
void print(int v, nodesNames a[])
{
    printf("\nThe distance array is\n");
    for (int i = 0; i < v; i++)
    {
        printf("%d ", distance[i]);
        printf("%s \n", a[i].areaName);
    }
    printf("\n");
    return;
}

// Function: writeGraphToFile
// Description: Writes the adjacency matrix to a file named "dijkstraNodes.txt"
// Input parameter: cost - adjacency matrix
// Return type: void
void writeGraphToFile(int cost[MAX_VERTICES][MAX_VERTICES])
{
    fp = fopen("dijkstraNodes.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file");
        return;
    }

    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        for (int j = i + 1; j < MAX_VERTICES; ++j)
        {
            if (cost[i][j] != 0)
            {
                fprintf(fp, "%d %d %d\n", i, j, cost[i][j]);
            }
        }
    }

    fclose(fp);
}

// Function: generateRandomEdges
// Description: Generates random edges for the graph, creating a connected graph
// Input parameter: cost - adjacency matrix
// Return type: void
void generateRandomEdges(int cost[MAX_VERTICES][MAX_VERTICES])
{

    // Create a connected graph
    for (int i = 1; i < MAX_VERTICES; ++i)
    {
        int edge1 = i;
        int edge2 = rand() % i;  // Connect to a random node before the current one
        int weight = rand() % 10 + 1;  // Random weight between 1 and 10
        cost[edge1][edge2] = weight;
        cost[edge2][edge1] = weight;  // Assuming an undirected graph
    }
    return;
}

// Function: assignCostMatrixValue
// Description: Initializes the adjacency matrix with a large value (9999) for non-edges
// Input parameter: m - adjacency matrix
// Return type: void
void assignCostMatrixValue(int m[][MAX_VERTICES])
{
    for(int i= 0; i<MAX_VERTICES; i++)
    {
        for(int j = 0; j < MAX_VERTICES; j++)
        {
            m[i][j] = 9999;
        }
        m[i][i] = 0;
    }
    return;
}

// Function: loadThenodeNames
// Description: Loads node names from the file "DijktrasNodesAreaRelation.txt"
// Input parameters: a - array of nodesNames, fp - file pointer
// Return type: int - number of nodes loaded
int loadThenodeNames(nodesNames a[], FILE* fp)
{
    int i = 0;
    fp = fopen("DijktrasNodesAreaRelation.txt", "r");
    if(fp == NULL)
    {
        printf("Error in opeaning in dijktras.txt\n");
        return -1;
    }
    while(!feof(fp))
    {
        fscanf(fp,"%d %s",&a[i].index, &a[i].areaName);
        i++;
    }
    fclose(fp);
    return i;
}

// Function: BruteForceStringMatch
// Description: Performs a brute-force string matching algorithm
// Input parameters: t - text, p - pattern, n - size of text, m - size of pattern
// Return type: int - 1 if pattern found, 0 otherwise
int BruteForceStringMatch(char t[], char p[], int n, int m)
{
    for(int i = 0; i < n; i++)
    {
        if(t[i] != p[i])
        {
            return 0;
        }
    }
    return 1;
}

// Function: findSource
// Description: Finds the index of the source node in the nodesNames array
// Input parameters: source - source node name, a - array of nodesNames, v - number of vertices
// Return type: int - index of the source node, -1 if not found
int findSource(char source[], nodesNames a[], int v)
{
    for(int i =0; i < v; i++)
    {
        if(strlen(source) == strlen(a[i].areaName))
        {
            if(BruteForceStringMatch(source, a[i].areaName, strlen(source), strlen(a[i].areaName)))
            {
                return i;
            }
        }
    }
    return -1;
}


// Function: printAreaNames
// Description: Prints the names of areas from the nodesNames array
// Input parameters: n - number of vertices, a - array of nodesNames
// Return type: void
void printAreaNames(int n, nodesNames a[])
{

    for(int i=0; i<n; i++)
    {
        printf("%s\n",a[i].areaName);
    }
    return;
}


// Function: printPath
// Description: Prints the shortest path from source to destination using the path array
// Input parameters: path - array representing the shortest path, src - source node index,
//                   dest - destination node index, a - array of nodesNames
// Return type: void
void printPath(int path[], int src, int dest, nodesNames a[])
{
    if (dest == src)
    {
        printf("%s ", a[src].areaName);
        return;
    }

    printPath(path, src, path[dest], a);
    printf("%s ", a[dest].areaName);
    return;
}
