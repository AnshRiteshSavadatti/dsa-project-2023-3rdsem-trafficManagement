#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// DFS_Names structucture  
struct DFS_Names{
    int number;
    char name[50];
};

typedef struct DFS_Names DFS_Names;

// Define a Node structure for the linked list
struct Node {
    int data;
    struct Node *next;
};

// Define a Stack structure with a top pointer
struct Stack {
    struct Node *top;
};

// Define a typedef for a pointer to Stack as stack
typedef struct Stack *stack;

// Function to initialize the stack
void initstack(stack s) {
    s->top = NULL;
}

// Function to check if the stack is empty
int isempty(stack s) {
    return s->top == NULL;
}

// Function to push a new element onto the stack
void push(stack s, int data) {
    // Allocate memory for a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
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
int pop(stack s) {
    // Check for stack underflow
    if (isempty(s)) {
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
void dfs(int graph[MAX][MAX], int n, int start, DFS_Names a[]) {
    // Allocate memory for the stack structure
    stack s = (stack)malloc(sizeof(struct Stack));
    if (s == NULL) {
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
    while (!isempty(s)) {
        // Pop a node from the stack
        int node = pop(s);

        // Process the node if not visited
        if (!visited[node]) {
            printf("%d %s\n", node, a[node].name);
            visited[node] = 1;

            // Push unvisited neighbors onto the stack
            for (int i = 0; i < n; i++) {
                if (graph[node][i] && !visited[i]) {
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
void fillValue(FILE *fp, int m[][MAX]) {
    fp = fopen("DFS_Edges.txt", "r");
    while (!feof(fp)) {
        int x, y, z;
        fscanf(fp, "%d %d %d", &x, &y, &z);
        m[x][y] = z;
    }
    fclose(fp);
    return;
}

void fillNames(FILE *fp, DFS_Names a[]){
    fp = NULL;
     fp = fopen("DijktrasNodesAreaRelation.txt", "r");
    int i=0;
    if(fp == NULL){
        printf("File Not found ");
        exit(0);
    }
    while(!feof(fp)){
        fscanf(fp, "%d %s", &a[i].number, &a[i].name);
        i++;
    }
    fclose(fp);
    return;
}

// Main function
int main() {
    // Declare variables
    int n, start;
    FILE *fp;
    int graph[MAX][MAX];

    // Input the number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Input the adjacency matrix from a fill
    printf("Enter the adjacency matrix:\n");
    fillValue(fp, graph);

     // allocating memmory for nodes
    DFS_Names * Names = (DFS_Names*) malloc (MAX *sizeof(DFS_Names));
    fillNames(fp, Names);

    // Input the starting vertex for DFS
    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &start);

    // Perform DFS and display the result
    dfs(graph, n, start, Names);

    // Return from the main function
    return 0;
}
