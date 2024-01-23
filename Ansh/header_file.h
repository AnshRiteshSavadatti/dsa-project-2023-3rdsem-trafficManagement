#ifndef HEADER_FILE_H_INCLUDED
#define HEADER_FILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <time.h>


// Keeps a log of activity. Any errors can be checked in this file
FILE *flog;

// definig constants
#define MAX_VERTICES 100

// Below mentioned are error status/status codes
#define SUCCESS                     1
#define FAILURE                     -1
#define FILE_OPEN_ERROR             1001
#define MEMORY_ALLOCATION_ERROR     1002
#define FILE_DELETE_ERROR           1003
#define COUNT_EXCEED_ERROR          1004
#define RESULT_NOT_FOUND            1005
#define FILE_EMPTY_ERROR            1006
#define STATUS_STACK_OVERFLOW      -1073741571


//**************************** smart speed bump **********************************************************
// Structure to represent a smart speed bump
typedef struct SpeedBump {
    int lane_number;
    bool activated;        // Status of the speed bump (true if activated, false if deactivated)
    int traffic_level;     // Traffic level for the lane (for simplicity, using an integer here)
    struct SpeedBump* left;
    struct SpeedBump* right;
} SpeedBump;

// Function prototypes

SpeedBump* createSpeedBump(int laneNumber, int trafficLevel, bool activated);
SpeedBump* insertSpeedBump(SpeedBump* root, int laneNumber, int trafficLevel, bool activated);
SpeedBump* adjustSpeedBumpActivation(SpeedBump* root, int laneNumber, int newTrafficLevel);
void displaySpeedBumps(SpeedBump* root);
void freeSpeedBumps(SpeedBump* root);
void writeToFile(SpeedBump* root, FILE* fp);

//************************************* AllocationOfPoliceOfficers ***********************************************************

// Define the structure for a junction node
struct Junction {
    int junction_no;
    int traffic_level;
    int num_police_officers;
    struct Junction* left;
    struct Junction* right;
    int height;
};

typedef struct Junction* JunctionNode;

JunctionNode* root;

// Function prototypes
JunctionNode createJunction(int junction_no, int traffic_level, int num_police_officers);
int height(JunctionNode node);
JunctionNode rightRotate(JunctionNode x);
JunctionNode leftRotate(JunctionNode x);
JunctionNode rotate(JunctionNode node);
JunctionNode insertJunction(JunctionNode root, int junction_no, int traffic_level, int num_police_officers);
JunctionNode assignOfficers(JunctionNode root, int junction_no, int trafficLevel);
void freeAVLTree(JunctionNode root);
void printInorder(JunctionNode root);
void writeFile(FILE* fp, JunctionNode root);
//************************************* KruskalsMinimalSpanningTree ***********************************************************

// making relation between node and area
typedef struct dataNodesNames{
    int n;
    char name[50];
    struct dataNodesNames* next;
}Node;
Node* data;

// structure to store vertices and weight between them
typedef struct node{
    int u;
    int v;
    int w;
}NODE;
NODE* edges;

// Function prototypes
void fillSpanningFile(FILE *fp);
void displayData(int n, Node data[]);
char* generate_random_string(int length);
void fillKruskalsFile(FILE* fp);
void readKruskals(FILE* fp, Node data[]);
void swap(NODE* a, NODE* b);
int partition(NODE a[], int l, int r);
void quickSort(NODE edges[], int l, int r);
int find(int arr[], int u, int v);
void union_(int arr[], int n, int u, int v);
int kruskals(NODE edges[], int n, int arr[]);


//************************************* Dijktras Algorithm ***********************************************************

// creating a structure for storing index {node} and areaName to implement dijktras
typedef struct nodesNames{
    int index;
    char areaName[50];
}nodesNames;

void heapify(int h[], int n);
int deleteMin(int arr[], int* n);
void dijkstras(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src);
void print(int v, nodesNames a[]);
void writeGraphToFile(int cost[MAX_VERTICES][MAX_VERTICES]);
void generateRandomEdges(int cost[MAX_VERTICES][MAX_VERTICES]);
void assignCostMatrixValue(int m[][MAX_VERTICES]);
int loadThenodeNames(nodesNames a[], FILE* fp);
int BruteForceStringMatch(char t[], char p[], int n, int m);
int findSource(char source[], nodesNames a[], int v);
void printAreaNames(int n, nodesNames a[]);


//*************************************  DFS Traversal ***********************************************************
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

struct Stack {
    struct Node *top;
};

// Define a typedef for a pointer to Stack as stack
typedef struct Stack *stack;

// Function prototypes
void initstack(stack s);
int isempty(stack s);
void push(stack s, int data);
int pop(stack s);
void dfs(int graph[MAX][MAX], int n, int start, DFS_Names a[]);
void fillValue(FILE *fp, int m[][MAX]);
void fillNames(FILE *fp, DFS_Names a[]);


//*************************************  prioritize vehicles ***********************************************************
// vehicle structure

struct queue{
    int priority;
    char name[50];
    char number[50];
    struct queue* next;
};

// typedef the queue
typedef struct queue* Queue;

int isEmpty(Queue head);
Queue FindMid(Queue head);
Queue Merge(Queue left, Queue right);
Queue MergeSort(Queue head);
char* Generate_random_string(int length);
Queue insert_data(Queue n);
Queue create();
Queue insert_at_end(Queue head);
Queue delete_from_front(Queue head);
void writeToFileQueue(FILE* fp, Queue head);


#endif // HEADER_FILE_H_INCLUDED
