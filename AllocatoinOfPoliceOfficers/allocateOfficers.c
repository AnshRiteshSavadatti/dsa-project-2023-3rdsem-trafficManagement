// 24 👨‍💻
#include <stdio.h>
#include <stdlib.h>

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

// to insert the nodes in tree
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
            // 35 - 70 2 officers
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
        }
    }
    return root;
}

// // assigining police officiers according to the given conditions below
// Junction* assignOfficers(Junction * root, int junction, int trafficLevel){
//     if(root != NULL){
//         if(junction < root->junction_no){
//             assignOfficers(root->right, junction, trafficLevel);
//         }else if(junction > root->junction_no){
//             assignOfficers(root->left, junction, trafficLevel);
//         }else{
//             // taking few cases here
//             // if trafficLevel 0 - 20 0 officers
//             // 20 - 35 1 officer
//             // 35 - 70 2 officer
//             if(trafficLevel <= 20){
//                 root->num_police_officers = 0;
//                 root->traffic_level = trafficLevel;
//             }else if(trafficLevel > 70){
//                 root->num_police_officers = 2;
//                 root->traffic_level = trafficLevel;
//             }else{
//                 root->num_police_officers = 1;
//                 root->traffic_level = trafficLevel;
//             }
//             return root;
//         }
//     }
// }

// Function to free the allocated memory for the junction tree
void freeJunctionTree(Junction* junction) {
    if (junction == NULL) {
        return;
    }

    freeJunctionTree(junction->left);
    freeJunctionTree(junction->right);
    free(junction);
}

// a function to print the values in tree
void printInorder(Junction* root){
    if(root != NULL){
        printInorder(root->left);
        printf("%d %d %d \n", root->junction_no, root->traffic_level, root->num_police_officers);
        printInorder(root->right);
    }
}

// a function to write in file
void writeFile(FILE*fp, Junction* root){
    if(root != NULL){
        writeFile(fp, root->left);
        fprintf(fp, "%d %d %d \n", root->junction_no, root->traffic_level, root->num_police_officers);
        writeFile(fp, root->right);
    }
    return;
}

int main() {
    // Build the junction tree
    Junction* root = NULL;

    FILE * fp = fopen("file.txt", "r");
    // reading input from file
    while(!feof(fp)){
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
    

    // taking user input for traffic level at a particular junctoin
    printf("Enter the Junction number\n");
    int junction, trafficlevel;
    scanf("%d",&junction);
    printf("Enter the trafficLevel\n");
    scanf("%d",&trafficlevel);
    // printf("Before assigned function\n");
    // printInorder(root);
    root = assignOfficers(root, junction, trafficlevel);

    // printing the assigned officers after updation
    printf("The officers after updation\n");
    printInorder(root);

    // writing back in file
    fp = fopen("file.txt", "w");
    writeFile(fp, root);

    // Free the allocated memory for the junction tree
    freeJunctionTree(root);

    return 0;
}
