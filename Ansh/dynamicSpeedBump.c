#include "header_file.h"
#include "constants.c"

// Function to fill random 1000 values in file of traffic level
void filldynamicSpeedBump(FILE* fp){
    // the printing sequence will be i rand%100 1||0
    srand(time(NULL));
    fp = fopen("dynamicSpeedBump.txt", "w");
    for(int i=0; i<10000; i++){
        fprintf(fp, "%d %d %d\n", i, rand() %100 + 1 , rand() % 2 );
    }
    fclose(fp);
    return;
}
// Function to create a new smart speed bump
SpeedBump* createSpeedBump(int laneNumber, int trafficLevel, bool activated) {
    SpeedBump* newSpeedBump = (SpeedBump*)malloc(sizeof(SpeedBump));
    newSpeedBump->lane_number = laneNumber;
    newSpeedBump->traffic_level = trafficLevel;
    newSpeedBump->activated = activated;
    newSpeedBump->left = NULL;
    newSpeedBump->right = NULL;
    return newSpeedBump;
}

// Function to insert a new speed bump into the binary search tree
SpeedBump* insertSpeedBump(SpeedBump* root, int laneNumber, int trafficLevel, bool activated) {
    if (root == NULL)
        return createSpeedBump(laneNumber, trafficLevel, activated);

    if (laneNumber < root->lane_number)
        root->left = insertSpeedBump(root->left, laneNumber, trafficLevel, activated);
    else if (laneNumber > root->lane_number)
        root->right = insertSpeedBump(root->right, laneNumber, trafficLevel, activated);
    else // Duplicate lanes are not allowed in this example
        return root;

    return root;
}

// Function to activate or deactivate a speed bump based on traffic conditions
SpeedBump* adjustSpeedBumpActivation(SpeedBump* root, int laneNumber, int newTrafficLevel) {
    SpeedBump* current = root;

    while (current != NULL) {
        if (laneNumber < current->lane_number)
            current = current->left;
        else if (laneNumber > current->lane_number)
            current = current->right;
        else {
            // Found the speed bump with the specified lane number
            // Assuming 15 to be the base case ie if the traffic is greater then 15 speed bump will be activated
            if (newTrafficLevel > 15) {
                current->activated = true;
            } else {
                current->activated = false;
            }
            current->traffic_level = newTrafficLevel;
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
               root->lane_number, root->activated ? "Activated" : "Deactivated", root->traffic_level);
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
        fprintf(fp, "%d %d %d\n", root->lane_number, root->traffic_level, root->activated);
        writeToFile(root->right, fp);
    }
    return;
}
