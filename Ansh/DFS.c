#include "header_file.h"
#include "constants.c"

// Function: initstack
// Description: Initializes the stack by setting the top pointer to NULL
// Input parameter: s - stack structure
// Return type: void
void initstack(stack s)
{
    s->top = NULL;
}

// Function to check if the stack is empty
// Function: isempty
// Description: Checks if the stack is empty
// Input parameter: s - stack structure
// Return type: int - 1 if empty, 0 otherwise
int isempty(stack s)
{
    return s->top == NULL;
}

// Function to push a new element onto the stack
// Function: push
// Description: Pushes a new element onto the stack
// Input parameters: s - stack structure, data - data to be pushed
// Return type: void
void push(stack s, int data)
{
    // Allocate memory for a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Set data and link the new node to the current top
    newNode->data = data;
    newNode->next = s->top;

    // Update the top pointer to the new node
    s->top = newNode;
}

// Function to pop an element from the stack
// Function: pop
// Description: Pops an element from the stack
// Input parameter: s - stack structure
// Return type: int - popped data
int pop(stack s)
{
    // Check for stack underflow
    if (isempty(s))
    {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }

    // Save the current top node
    struct Node *temp = s->top;

    // Get data and update the top pointer to the next node
    int data = temp->data;
    s->top = temp->next;

    // Free the memory of the popped node
    free(temp);

    // Return the popped data
    return data;
}

// Function to perform depth-first search (DFS)
// Function: dfs
// Description: Performs depth-first search (DFS) on a graph
// Input parameters: graph - adjacency matrix, n - number of vertices,
//                   start - starting node, a - array containing names
// Return type: void
void dfs(int graph[MAX][MAX], int n, int start, DFS_Names a[])
{
    // Allocate memory for the stack structure
    stack s = (stack)malloc(sizeof(struct Stack));
    if (s == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Array to track visited nodes
    int visited[MAX] = {0};

    // Initialize the stack
    initstack(s);

    // Push the starting node onto the stack
    push(s, start);

    // Display the initial message
    printf("DFS Order: ");

    // Perform DFS
    while (!isempty(s))
    {
        // Pop a node from the stack
        int node = pop(s);

        // Process the node if not visited
        if (!visited[node])
        {
            printf("%d %s\n", node, a[node].name);
            visited[node] = 1;

            // Push unvisited neighbors onto the stack
            for (int i = 0; i < n; i++)
            {
                if (graph[node][i] && !visited[i])
                {
                    push(s, i);
                }
            }
        }
    }

    // Free the stack memory
    free(s);

    // Display a newline character after DFS completion
    printf("\n");
}

// Function to fill the adjacency matrix from a file
// Function: fillValue
// Description: Fills the adjacency matrix from a file
// Input parameters: fp - file pointer, m - adjacency matrix
// Return type: void
void fillValue(FILE *fp, int m[][MAX])
{
    fp = fopen("DFS_Edges.txt", "r");
    while (!feof(fp))
    {
        int x, y, z;
        fscanf(fp, "%d %d %d", &x, &y, &z);
        m[x][y] = z;
    }
    fclose(fp);
    return;
}

// Function: fillNames
// Description: Fills the DFS_Names array from a file
// Input parameters: fp - file pointer, a - array of DFS_Names structures
// Return type: void
void fillNames(FILE *fp, DFS_Names a[])
{
    fp = NULL;
    fp = fopen("DijktrasNodesAreaRelation.txt", "r");
    int i=0;
    if(fp == NULL)
    {
        printf("File Not found ");
        exit(0);
    }
    while(!feof(fp))
    {
        fscanf(fp, "%d %s", &a[i].number, &a[i].name);
        i++;
    }
    fclose(fp);
    return;
}
