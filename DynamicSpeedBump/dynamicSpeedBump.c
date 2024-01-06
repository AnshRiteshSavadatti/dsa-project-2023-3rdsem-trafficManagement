#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
void adjustSpeedBumpActivation(SpeedBump* root, int laneNumber, int newTrafficLevel) {
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
            return;
        }
    }

    // Lane not found
    printf("Lane not found: %d\n", laneNumber);
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

// Main function for testing
int main() {
    SpeedBump* speedBumpTree = NULL;

    // the input which we need is lane number and trafficLevel
    // we will be using files here
    // Adding smart speed bumps dynamically
    FILE * fp = fopen("dynamicSpeedBump.txt", "r");

    /// Checking if file is found
    if(fp == NULL){
        printf("File not found \n");
        return -1;
    }
    // until the end of file read all data
    while(!feof(fp)){
        int tLevel, Lane, status;
        fscanf(fp, "%d %d %d", &Lane, &tLevel, &status);
        speedBumpTree = insertSpeedBump(speedBumpTree, Lane, tLevel, status);
    }
    // speedBumpTree = insertSpeedBump(speedBumpTree, 1, 10, false); // Deactivated in Lane 1, Traffic Level: 10
    // speedBumpTree = insertSpeedBump(speedBumpTree, 2, 15, true);  // Activated in Lane 2, Traffic Level: 15
    // speedBumpTree = insertSpeedBump(speedBumpTree, 3, 12, false); // Deactivated in Lane 3, Traffic Level: 12

    // Displaying initial status of speed bumps
    printf("Initial Status of Smart Speed Bumps:\n");
    displaySpeedBumps(speedBumpTree);

    // Simulating dynamic activation or deactivation based on new traffic conditions
    adjustSpeedBumpActivation(speedBumpTree, 2, 18); // Activate a speed bump in Lane 2 (Traffic Level increased to 18)
    adjustSpeedBumpActivation(speedBumpTree, 1, 20);  // Activate a speed bump in Lane 1 (Traffic Level increased to 20)

    // Displaying updated status of speed bumps after dynamic adjustments
    printf("\nUpdated Status of Smart Speed Bumps:\n");
    displaySpeedBumps(speedBumpTree);

    // Free allocated memory
    freeSpeedBumps(speedBumpTree);

    return 0;
}
