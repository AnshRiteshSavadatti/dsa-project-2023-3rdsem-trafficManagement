// 24 👨‍💻
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

// *************************************************************************************
// Allocatoin of police officers 

// Define the structure for a junction node
typedef struct Junction {
    int junction_no;
    int traffic_level;
    int num_police_officers;
    struct Junction* left;
    struct Junction* right;
} Junction;

// Function to create a new junction node
Junction* createJunction(int junction_no, int traffic_level, int num_police_officers) {
    Junction* newJunction = (Junction*)malloc(sizeof(Junction));
    newJunction->junction_no = junction_no;
    newJunction->traffic_level = traffic_level;
    newJunction->num_police_officers = num_police_officers;
    newJunction->left = NULL;
    newJunction->right = NULL;
    return newJunction;
}

// to insert the nodes in the tree
Junction* insertJunction(Junction* root, int junction_no, int traffic_level, int num_police_officers) {
    if (root == NULL) {
        return createJunction(junction_no, traffic_level, num_police_officers);
    }

    if (junction_no < root->junction_no) {
        root->left = insertJunction(root->left, junction_no, traffic_level, num_police_officers);
    } else if (junction_no > root->junction_no) {
        root->right = insertJunction(root->right, junction_no, traffic_level, num_police_officers);
    }

    return root;
}

// Function to assign police officers based on traffic levels
int totalOfficersAssigned(Junction* junction) {
    if (junction == NULL) {
        return 0;
    }

    int totalOfficers = junction->num_police_officers;
    totalOfficers += totalOfficersAssigned(junction->left);
    totalOfficers += totalOfficersAssigned(junction->right);

    return totalOfficers;
}

// assigning police officers according to the given conditions below
Junction* assignOfficers(Junction* root, int junction, int trafficLevel) {
    if (root != NULL) {
        if (junction < root->junction_no) {
            root->left = assignOfficers(root->left, junction, trafficLevel);
        } else if (junction > root->junction_no) {
            root->right = assignOfficers(root->right, junction, trafficLevel);
        } else {
            // taking few cases here
            // if trafficLevel 0 - 20 0 officers
            // 20 - 35 1 officer
            // 35 - 70 2 officer
            if (trafficLevel <= 20) {
                root->num_police_officers = 0;
                root->traffic_level = trafficLevel;
            } else if (trafficLevel > 70) {
                root->num_police_officers = 2;
                root->traffic_level = trafficLevel;
            } else {
                root->num_police_officers = 1;
                root->traffic_level = trafficLevel;
            }
            return root;
        }
    }
}

// Function to free the allocated memory for the junction tree
void freeJunctionTree(Junction* junction) {
    if (junction == NULL) {
        return;
    }

    freeJunctionTree(junction->left);
    freeJunctionTree(junction->right);
    free(junction);
}

// a function to print the values in the tree
void printInorder(Junction* root) {
    if (root != NULL) {
        printInorder(root->left);
        printf("%d %d %d \n", root->junction_no, root->traffic_level, root->num_police_officers);
        printInorder(root->right);
    }
}

// a function to write in a file
void writeFile(FILE* fp, Junction* root) {
    if (root != NULL) {
        writeFile(fp, root->left);
        fprintf(fp, "%d %d %d \n", root->junction_no, root->traffic_level, root->num_police_officers);
        writeFile(fp, root->right);
    }
    return;
}

// *****************************************************************************************************************
// Dynamic speed bump

// Structure to represent a smart speed bump
typedef struct SpeedBump {
    int laneNumber;
    bool activated;        // Status of the speed bump (true if activated, false if deactivated)
    int trafficLevel;     // Traffic level for the lane (for simplicity, using an integer here)
    struct SpeedBump* left;
    struct SpeedBump* right;
} SpeedBump;

// Function to create a new smart speed bump
SpeedBump* createSpeedBump(int laneNumber, int trafficLevel, bool activated) {
    SpeedBump* newSpeedBump = (SpeedBump*)malloc(sizeof(SpeedBump));
    newSpeedBump->laneNumber = laneNumber;
    newSpeedBump->trafficLevel = trafficLevel;
    newSpeedBump->activated = activated;
    newSpeedBump->left = NULL;
    newSpeedBump->right = NULL;
    return newSpeedBump;
}

// Function to insert a new speed bump into the binary search tree
SpeedBump* insertSpeedBump(SpeedBump* root, int laneNumber, int trafficLevel, bool activated) {
    if (root == NULL)
        return createSpeedBump(laneNumber, trafficLevel, activated);

    if (laneNumber < root->laneNumber)
        root->left = insertSpeedBump(root->left, laneNumber, trafficLevel, activated);
    else if (laneNumber > root->laneNumber)
        root->right = insertSpeedBump(root->right, laneNumber, trafficLevel, activated);
    else // Duplicate lanes are not allowed in this example
        return root;

    return root;
}

// Function to activate or deactivate a speed bump based on traffic conditions
SpeedBump* adjustSpeedBumpActivation(SpeedBump* root, int laneNumber, int newTrafficLevel) {
    SpeedBump* current = root;

    while (current != NULL) {
        if (laneNumber < current->laneNumber)
            current = current->left;
        else if (laneNumber > current->laneNumber)
            current = current->right;
        else {
            // Found the speed bump with the specified lane number
            // Assuming 15 to be the base case ie if the traffic is greater then 15 speed bump will be activated 
            if (newTrafficLevel > 15) {
                current->activated = true;
            } else {
                current->activated = false;
            }
            current->trafficLevel = newTrafficLevel;
            return root;
        }
    }

    // Lane not found
    printf("Lane not found: %d\n", laneNumber);
    return root;
}

// Function to display the status of each speed bump in the binary search tree
void displaySpeedBumps(SpeedBump* root) {
    if (root != NULL) {
        displaySpeedBumps(root->left);
        printf("Lane %d - Speed Bump Status: %s - Traffic Level: %d\n",
               root->laneNumber, root->activated ? "Activated" : "Deactivated", root->trafficLevel);
        displaySpeedBumps(root->right);
    }
}

// Function to free allocated memory
void freeSpeedBumps(SpeedBump* root) {
    if (root != NULL) {
        freeSpeedBumps(root->left);
        freeSpeedBumps(root->right);
        free(root);
    }
}

void writeToFile(SpeedBump* root, FILE* fp){
    if(root != NULL){
        writeToFile(root->left, fp);
        fprintf(fp, "%d %d %d\n", root->laneNumber, root->trafficLevel, root->activated);
        writeToFile(root->right, fp);
    }
    return;
}

// ************************************************************************************************************************************
// working on kruskals algorithm
// creating structure for dataNodeNames to connect nodes and names
typedef struct dataNodesNames{
    int n;
    char name[50];
    struct dataNodesNames* next;
}Node;
Node data[30];

// creating a structure which the nodes and weight between them 
typedef struct node{
    int u;
    int v;
    int w;
    char placeName[50];
}NODE;

NODE edges[30];

// function to swap two nodes
void swap(NODE* a, NODE* b){
    NODE temp = *a;
    *a = *b;
    *b = temp;
    return;
}

// quick partition code
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

// quickSort ie sorting the edges
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

// find function
int find(int arr[], int u, int v){
    if(arr[u] == arr[v])
        return 1;
    return 0;
}

// union function
void union_(int arr[], int n, int u, int v){
    int temp = arr[u];
    for(int i=0; i<n; i++){
        if(arr[i] == temp)
            arr[i] = arr[v];
    }
    return;
}

// Implementation of Kruskals algorithm
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

// program to display the connections between the nodes and names of location
void displayData(int n){
    for(int i=0; i<n; i++){
        printf("%d %s\n",data[i].n, data[i].name);
    }
    return;
}


// writing a main function to the above functions 
int main() {
    int n;
    Junction* root = NULL;
    FILE* fp;
    SpeedBump* speedBumpTree = NULL;
    Node* head = NULL;

//  Reading data for Allocation of police officers
    fp = fopen("file.txt", "r");
    // reading input from file
    while (!feof(fp)) {
        int jn, tl, npo;
        fscanf(fp, "%d %d %d", &jn, &tl, &npo);
        root = insertJunction(root, jn, tl, npo);
    }
    fclose(fp);

    // Reading officers for Dynamic Speed Bumps
    FILE * fpp = fopen("dynamicSpeedBump.txt", "r");
    /// Checking if file is found
    if(fpp == NULL){
        printf("File not found \n");
        return -1;
    }
    // until the end of file read all data
    while(!feof(fpp)){
        int tLevel, Lane, status;
        fscanf(fpp, "%d %d %d", &Lane, &tLevel, &status);
        speedBumpTree = insertSpeedBump(speedBumpTree, Lane, tLevel, status);
    }
    fclose(fpp);

    // reading the file for minimal spaning tree
    FILE * f = fopen("kruskalsRepresentation.txt","r");
    int j = 0;
    while(!feof(f)){
        fscanf(f,"%d %s",&data[j].n, &data[j].name);
        j++;
    }
    // closing the file
    fclose(f);

    while (1) {
        printf("Enter\n");
        printf("1 to know and change the position of officers\n");
        printf("2 to look at dynamic speed bumps and update them\n");
        printf("3 to generate a minimal spanning tree for given nodes\n");
        // taking input for switch case
        int ch;
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                fp = fopen("file.txt", "r");
                // reading input from file
                while (!feof(fp)) {
                    int jn, tl, npo;
                    fscanf(fp, "%d %d %d", &jn, &tl, &npo);
                    root = insertJunction(root, jn, tl, npo);
                }
                fclose(fp);
                // print the inserted values
                printf("The officers before updation\n");
                printInorder(root);

                // Total police officers assigned
                int totalAssignedOfficers = totalOfficersAssigned(root);

                // Display the total number of officers assigned
                printf("Total number of police officers assigned: %d\n", totalAssignedOfficers);

                while (1) {
                    printf("Enter\n1 if you want to change the traffic level at a particular junction ");
                    printf("{which will change the allocation of officers}, Else 0\n");
                    int choice;
                    scanf("%d", &choice);
                    if(choice == 1){
                        // taking user input for traffic level at a particular junction
                        printf("Enter the Junction number\n");
                        int junction, trafficlevel;
                        scanf("%d", &junction);
                        printf("Enter the trafficLevel\n");
                        scanf("%d", &trafficlevel);
                        root = assignOfficers(root, junction, trafficlevel);

                        // printing the assigned officers after updation
                        printf("The officers after updation\n");
                        printInorder(root);

                        // writing back to the file
                        fp = fopen("file.txt", "w");
                        writeFile(fp, root);
                        fclose(fp);  // Close the file after writing
                    }
                    else{
                        break;
                    }
                    }
                // Free the allocated memory for the junction tree
                freeJunctionTree(root);
                break;
            case 2 :
                printf("Initial Status of Smart Speed Bumps:\n");
                displaySpeedBumps(speedBumpTree);

                // Simulating dynamic activation or deactivation based on new traffic conditions
                while(1){
                    int choice = 0;
                    printf("Enter 1 to update the status of speed bump");
                    printf(" {which will write it to file} or else 0\n");
                    scanf("%d",&choice);
                    int ln, tn;
                    if(choice == 1){
                        /* code */
                        printf("Enter the lane number\n");
                        scanf("%d",&ln);
                        printf("Enter the traffic level\n");
                        scanf("%d",&tn);
                        speedBumpTree = adjustSpeedBumpActivation(speedBumpTree, ln, tn);
                        // Displaying updated status of speed bumps after dynamic adjustments
                        printf("\nUpdated Status of Smart Speed Bumps:\n");
                        displaySpeedBumps(speedBumpTree);
                    }else{
                        break;
                    }
                }
                // adjustSpeedBumpActivation(speedBumpTree, 2, 18); // Activate a speed bump in Lane 2 (Traffic Level increased to 18)
                // adjustSpeedBumpActivation(speedBumpTree, 1, 20);  // Activate a speed bump in Lane 1 (Traffic Level increased to 20)

                
                // writing the data back to secondary memory
                fp = fopen("dynamicSpeedBump.txt", "w");
                if(fp == NULL){
                    printf("dynamicSpeedBump file not found\n");
                    return -1;
                }
                writeToFile(speedBumpTree, fp);
                fflush(fp);
                // Closing the file after writing
                fclose(fp);

                // Free allocated memory
                freeSpeedBumps(speedBumpTree);
                break;
            case 3 : 
                printf("Enter the number of edges\n");
                scanf("%d",&n);
                 printf("The relation between the nodes and the names in city are \n");
                displayData(j);
                // Reading input from file spanning.txt
                fp = fopen("spanning.txt", "r");
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
                break;
            default:
                exit(0);
        }
    }
    return 0;
}
