#include "header_file.h"
#include "constants.c"

void fillFile(FILE * fp){
    fp = fopen("file.txt", "w");
    srand(time(NULL));
    for(int i=0; i<40000; i++){
        // the input must go as
        // i, rand() % 101, 0

        int random = rand()%101;
        fprintf(fp, "%d %d ", i, random);
        if(random <= 20){
            fprintf(fp, "%d\n", 0);
        }else if(random > 70){
            fprintf(fp, "%d\n", 2);
        }else{
            fprintf(fp, "%d\n", 1);
        }
    }
    fclose(fp);
    return;
}
// Function to create a new junction node
JunctionNode createJunction(int junction_no, int traffic_level, int num_police_officers) {
    JunctionNode newJunction = (JunctionNode)malloc(sizeof(struct Junction));
    newJunction->junction_no = junction_no;
    newJunction->traffic_level = traffic_level;
    newJunction->num_police_officers = num_police_officers;
    newJunction->left = NULL;
    newJunction->right = NULL;
    newJunction->height = 0;
    return newJunction;
}

// Function to get the height of a junction node
int height(JunctionNode node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

// Function to perform right rotation
JunctionNode rightRotate(JunctionNode x) {
    JunctionNode y = x->left;
    JunctionNode z = y->right;

    y->right = x;
    x->left = z;

    y->height = (height(y->left) > height(y->right) ? height(y->left) : height(y->right)) + 1;
    x->height = (height(x->left) > height(x->right) ? height(x->left) : height(x->right)) + 1;

    return y;
}

// Function to perform left rotation
JunctionNode leftRotate(JunctionNode x) {
    JunctionNode y = x->right;
    JunctionNode z = y->left;

    y->left = x;
    x->right = z;

    y->height = (height(y->left) > height(y->right) ? height(y->left) : height(y->right)) + 1;
    x->height = (height(x->left) > height(x->right) ? height(x->left) : height(x->right)) + 1;

    return y;
}

// Function to perform AVL tree rotation
JunctionNode rotate(JunctionNode node) {
    if (height(node->left) - height(node->right) > 1) {
        // left heavy
        if (height(node->left->left) - height(node->left->right) > 0) {
            // left left case
            return rightRotate(node);
        }
        if (height(node->left->left) - height(node->left->right) < 0) {
            // left right case
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    } else if (height(node->left) - height(node->right) < -1) {
        // right heavy
        if (height(node->right->left) - height(node->right->right) < 0) {
            // right right case
            return leftRotate(node);
        }
        if (height(node->right->left) - height(node->right->right) > 0) {
            // left right case
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

// Function to insert a junction node into the AVL tree
JunctionNode insertJunction(JunctionNode root, int junction_no, int traffic_level, int num_police_officers) {
    if (root == NULL) {
        return createJunction(junction_no, traffic_level, num_police_officers);
    }

    if (junction_no < root->junction_no) {
        root->left = insertJunction(root->left, junction_no, traffic_level, num_police_officers);
    } else if (junction_no > root->junction_no) {
        root->right = insertJunction(root->right, junction_no, traffic_level, num_police_officers);
    }

    root->height = (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;

    return rotate(root);
}

// Function to assign police officers based on traffic levels
JunctionNode assignOfficers(JunctionNode root, int junction_no, int trafficLevel) {
    if (root != NULL) {
        if (junction_no < root->junction_no) {
            root->left = assignOfficers(root->left, junction_no, trafficLevel);
        } else if (junction_no > root->junction_no) {
            root->right = assignOfficers(root->right, junction_no, trafficLevel);
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
    return root;
}

// Function to free the allocated memory for the AVL tree
void freeAVLTree(JunctionNode root) {
    if (root == NULL) {
        return;
    }

    freeAVLTree(root->left);
    freeAVLTree(root->right);
    free(root);
}

// Function to print the values in the AVL tree
void printInorder(JunctionNode root) {
    if (root != NULL) {
        printInorder(root->left);
        printf("%d %d %d\n", root->junction_no, root->traffic_level, root->num_police_officers);
        printInorder(root->right);
    }
}

// Function to write in a file
void writeFile(FILE* fp, JunctionNode root) {
    if (root != NULL) {
        writeFile(fp, root->left);
        fprintf(fp, "%d %d %d\n", root->junction_no, root->traffic_level, root->num_police_officers);
        writeFile(fp, root->right);
    }
}

// Function to assign police officers based on traffic levels
int totalOfficersAssigned(JunctionNode  junction) {
    if (junction == NULL) {
        return 0;
    }

    int totalOfficers = junction->num_police_officers;
    totalOfficers += totalOfficersAssigned(junction->left);
    totalOfficers += totalOfficersAssigned(junction->right);

    return totalOfficers;
}

void freeJunctionTree(JunctionNode junction) {
    if (junction == NULL) {
        return;
    }

    freeJunctionTree(junction->left);
    freeJunctionTree(junction->right);
    free(junction);
}




