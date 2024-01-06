#include <stdio.h>
#include <stdlib.h>

struct Road {
    int roadId;
    int speedLimit;
    int trafficLevel;
    struct Road *left;
    struct Road *right;
};

struct Road *createRoad(int roadId, int speedLimit, int trafficLevel) {
    struct Road *newRoad = (struct Road *)malloc(sizeof(struct Road));
    newRoad->roadId = roadId;
    newRoad->speedLimit = speedLimit;
    newRoad->trafficLevel = trafficLevel;
    newRoad->left = NULL;
    newRoad->right = NULL;
    return newRoad;
}

struct Road *insertRoad(struct Road *root, int roadId, int speedLimit, int trafficLevel) {
    if (root == NULL) {
        return createRoad(roadId, speedLimit, trafficLevel);
    }

    if (roadId < root->roadId) {
        root->left = insertRoad(root->left, roadId, speedLimit, trafficLevel);
    } else if (roadId > root->roadId) {
        root->right = insertRoad(root->right, roadId, speedLimit, trafficLevel);
    } else {
        root->speedLimit = speedLimit;
        root->trafficLevel = trafficLevel;
    }

    return root;
}

// struct Road *insertRoad(struct Road *root, int roadId, int speedLimit, int trafficLevel){

// }

// struct Road *updateSpeedLimit(struct Road *root, int roadId, int newTrafficLevel) {
//     if (root == NULL) {
//         printf("Road with ID %d not found.\n", roadId);
//         return root;
//     }

//     if (roadId < root->roadId) {
//         root->left = updateSpeedLimit(root->left, roadId, newTrafficLevel);
//     } else if (roadId > root->roadId) {
//         root->right = updateSpeedLimit(root->right, roadId, newTrafficLevel);
//     } else {
//         root->trafficLevel = newTrafficLevel;

//         // Adjust speed limit based on traffic level
//         if (newTrafficLevel >= 80) {
//             root->speedLimit = 50;
//         } else if (newTrafficLevel >= 50) {
//             root->speedLimit = 60;
//         } else {
//             root->speedLimit = 70;
//         }

//         printf("Speed limit for Road ID %d updated to %d based on traffic level %d.\n",
//                roadId, root->speedLimit, newTrafficLevel);
//     }

//     return root;
// }

struct Road *updateSpeedLimit(struct Road *root, int roadId, int newTrafficLevel){
    if (root == NULL) {
        printf("Road with ID %d not found.\n", roadId);
        return root;
    }
    struct Road* temp = root;
    while(temp != NULL && temp->roadId != roadId){
        if(temp->roadId < roadId){
            temp = temp->right;
        }else{
            temp = temp->left;
        }
    }
    if(temp == NULL){
        printf("Road ID %d Not Found\n",roadId);
    }else{
        if (newTrafficLevel >= 80) {
            root->speedLimit = 50;
        } else if (newTrafficLevel >= 50) {
            root->speedLimit = 60;
        } else {
            root->speedLimit = 70;
        }
    }
    return root;
}

void printInOrder(struct Road *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("Road ID: %d, Speed Limit: %d, Traffic Level: %d\n",
               root->roadId, root->speedLimit, root->trafficLevel);
        printInOrder(root->right);
    }
}

void writeToFile(struct Road *root, FILE *file) {
    if (root != NULL) {
        writeToFile(root->left, file);
        fprintf(file, "%d %d %d\n", root->roadId, root->speedLimit, root->trafficLevel);
        writeToFile(root->right, file);
    }
}

void freeBST(struct Road *root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main() {
    struct Road *root = NULL;
    int roadId, speedLimit, trafficLevel;

    // Open the file for reading
    FILE *file = fopen("Traffic.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file.\n");
        return 1;
    }

    // Read road information from the file
    while (fscanf(file, "%d %d %d", &roadId, &speedLimit, &trafficLevel) == 3) {
        root = insertRoad(root, roadId, speedLimit, trafficLevel);
    }

    // Close the file
    fclose(file);

    // Example: Print the initial state of the roads
    printf("Initial state of the roads:\n");
    printInOrder(root);

    // Take input for road ID and traffic level
    printf("\nEnter Road ID: ");
    scanf("%d", &roadId);
    printf("Enter Traffic Level: ");
    scanf("%d", &trafficLevel);

    // Update speed limit based on user input
    root = updateSpeedLimit(root, roadId, trafficLevel);

    // Open the file for writing (truncate the file)
    file = fopen("Traffic.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening the file for writing.\n");
        freeBST(root);
        return 1;
    }

    // Write the updated information back to the file
    writeToFile(root, file);

    // Close the file
    fclose(file);

    // Print the updated state of the roads
    printf("\nUpdated state of the roads:\n");
    printInOrder(root);

    // Free allocated memory
    freeBST(root);

    return 0;
}
