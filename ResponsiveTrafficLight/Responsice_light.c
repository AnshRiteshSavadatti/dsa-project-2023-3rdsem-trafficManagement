#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the tree node
struct TreeNode {
    int junctionNumber;
    int trafficLevel;
    char lightColor[10];
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* createNode(int junction, int level, const char* color) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->junctionNumber = junction;
    newNode->trafficLevel = level;
    strcpy(newNode->lightColor, color);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the tree
struct TreeNode* insertNode(struct TreeNode* root, int junction, int level, const char* color) {
    if (root == NULL) {
        return createNode(junction, level, color);
    }

    if (junction < root->junctionNumber) {
        root->left = insertNode(root->left, junction, level, color);
    } else if (junction > root->junctionNumber) {
        root->right = insertNode(root->right, junction, level, color);
    } else {
        // Junction number already exists, you may want to handle this case appropriately.
        printf("Error: Junction number %d already exists.\n", junction);
    }

    return root;
}

// Function to search for the appropriate light color based on traffic level
void searchLightColor(struct TreeNode* root, int junction, int level, char lightColor[]) {
    if (root == NULL) {
        strcpy(lightColor, "Unknown");
        return;
    }

    if (junction < root->junctionNumber) {
        searchLightColor(root->left, junction, level, lightColor);
    } else if (junction > root->junctionNumber) {
        searchLightColor(root->right, junction, level, lightColor);
    } else {
        // Found the matching junction number
        // taking 0 -35 as green
        // 35 - 55 orange
        // >55 green
        if (level <= 35) {
            strcpy(lightColor, "Green");
        } else if (level >= 55) {
            strcpy(lightColor, "Red");
        } else {
            strcpy(lightColor, "Orange");
        }
    }
}

int main() {
    struct TreeNode* root = NULL;
    int junctionNumber, trafficLevel;
    char lightColor[10];

    FILE * fp = fopen("Light.txt", "r");
    
    if(fp == NULL){
        printf("Light.txt file not found\n");
        return -1;
    }
    // reading the data from file
    while(!feof(fp)){
        if(fp != NULL){
            int a,b;
            char p[10]; 
            fscanf(fp, "%d %d %s",&a, &b, p);
            root = insertNode(root, a, b, p);
        }
    }
    // Build the binary tree with some sample data
    // root = insertNode(root, 1, 30, "Green");
    // root = insertNode(root, 2, 70, "Red");
    // root = insertNode(root, 3, 50, "Orange");

    // Get real-time traffic level and junction number
    printf("Enter junction number: ");
    scanf("%d", &junctionNumber);
    printf("Enter current traffic level (0-100): ");
    scanf("%d", &trafficLevel);

    // Search for the appropriate light color based on traffic level
    searchLightColor(root, junctionNumber, trafficLevel, lightColor);

    printf("Junction %d - Traffic level is %d. Setting street light to %s\n", junctionNumber, trafficLevel, lightColor);

    return 0;
}
