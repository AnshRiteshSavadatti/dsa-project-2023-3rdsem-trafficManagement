#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Junction {
    int junction_no;
    int traffic_level;
    int num_police_officers;
    int height;
    struct Junction* left;
    struct Junction* right;
} Junction;

Junction* root;

int height(Junction* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Junction* createJunction(int junction_no, int traffic_level, int num_police_officers) {
    Junction* newJunction = (Junction*)malloc(sizeof(Junction));
    newJunction->junction_no = junction_no;
    newJunction->traffic_level = traffic_level;
    newJunction->num_police_officers = num_police_officers;
    newJunction->height = 1;
    newJunction->left = NULL;
    newJunction->right = NULL;
    return newJunction;
}

Junction* rightRotate(Junction* y) {
    Junction* x = y->left;
    Junction* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Junction* leftRotate(Junction* x) {
    Junction* y = x->right;
    Junction* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Junction* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Junction* insertJunction(Junction* node, int junction_no, int traffic_level, int num_police_officers) {
    if (node == NULL)
        return createJunction(junction_no, traffic_level, num_police_officers);

    if (junction_no < node->junction_no)
        node->left = insertJunction(node->left, junction_no, traffic_level, num_police_officers);
    else if (junction_no > node->junction_no)
        node->right = insertJunction(node->right, junction_no, traffic_level, num_police_officers);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && junction_no < node->left->junction_no)
        return rightRotate(node);

    if (balance < -1 && junction_no > node->right->junction_no)
        return leftRotate(node);

    if (balance > 1 && junction_no > node->left->junction_no) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && junction_no < node->right->junction_no) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void freeAVLTree(Junction* junction) {
    if (junction == NULL)
        return;

    freeAVLTree(junction->left);
    freeAVLTree(junction->right);
    free(junction);
}

void fillFile(FILE * fp){
    fp = fopen("file.txt", "w");
    srand(time(NULL));
    for(int i=0; i<40000; i++){
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

void printInorder(Junction* root) {
    if (root != NULL) {
        printInorder(root->left);
        printf("%d %d %d \n", root->junction_no, root->traffic_level, root->num_police_officers);
        printInorder(root->right);
    }
}

void writeFile(FILE* fp, Junction* root) {
    if (root != NULL) {
        writeFile(fp, root->left);
        fprintf(fp, "%d %d %d \n", root->junction_no, root->traffic_level, root->num_police_officers);
        writeFile(fp, root->right);
    }
}

Junction* assignOfficers(Junction* root, int junction, int trafficLevel) {
    if (root != NULL) {
        if (junction < root->junction_no) {
            root->left = assignOfficers(root->left, junction, trafficLevel);
        } else if (junction > root->junction_no) {
            root->right = assignOfficers(root->right, junction, trafficLevel);
        } else {
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

int totalOfficersAssigned(Junction* junction) {
    if (junction == NULL) {
        return 0;
    }

    int totalOfficers = junction->num_police_officers;
    totalOfficers += totalOfficersAssigned(junction->left);
    totalOfficers += totalOfficersAssigned(junction->right);

    return totalOfficers;
}

int main() {
    FILE * fp;
    srand(time(NULL));
    root = NULL;
    fillFile(fp);
    fp = fopen("file.txt", "r");

    while (!feof(fp)) {
        int jn, tl, npo;
        fscanf(fp, "%d %d %d", &jn, &tl, &npo);
        root = insertJunction(root, jn, tl, npo);
    }
    fclose(fp);

    printf("The officers before updation\n");
    printInorder(root);

    int totalAssignedOfficers = totalOfficersAssigned(root);
    printf("Total number of police officers assigned: %d\n", totalAssignedOfficers);

    while (1) {
        printf("Enter\n1 if you want to change the traffic level at a particular junction ");
        printf("{which will change the allocation of officers}, Else 0\n");
        int choice;
        scanf("%d", &choice);
        if(choice == 1){
            printf("Enter the Junction number\n");
            int junction, trafficlevel;
            scanf("%d", &junction);
            printf("Enter the trafficLevel\n");
            scanf("%d", &trafficlevel);
            root = assignOfficers(root, junction, trafficlevel);

            printf("The officers after updation\n");
            printInorder(root);

            fp = fopen("file.txt", "w");
            writeFile(fp, root);
            fclose(fp);
        }
        else{
            break;
        }
    }

    freeAVLTree(root);

    return 0;
}
