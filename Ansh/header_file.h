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
#define MAX_VERTICES 20

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
typedef struct Junction {
    int junction_no;
    int traffic_level;
    int num_police_officers;
    struct Junction* left;
    struct Junction* right;
} Junction;
Junction* root;

// Function prototypes
Junction* createJunction(int junction_no, int traffic_level, int num_police_officers);
Junction* insertJunction(Junction* root, int junction_no, int traffic_level, int num_police_officers);
int totalOfficersAssigned(Junction* junction);
Junction* assignOfficers(Junction* root, int junction, int traffic_level);
void freeJunctionTree(Junction* junction);
void printInorder(Junction* root);
void writeFile(FILE* fp, Junction* root);

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

#endif // HEADER_FILE_H_INCLUDED
