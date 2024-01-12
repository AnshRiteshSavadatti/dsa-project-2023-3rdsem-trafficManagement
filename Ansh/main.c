#include "constants.c"
#include "dynamicSpeedBump.c"
#include "AllocationOfPoliceOfficers.c"
#include "MinimalSpanningTree.c"
#include "dijktrasAlgorithm.c"
#include <time.h>

void menu(){
    for(int i=0; i<120; i++){
        printf("*");
    }
    printf("\nMENU\n");
    printf("Enter\n");
    printf("1 to see and change the allocation of police officers\n");
    printf("2 to change and view current speed bumps\n");
    printf("3 to generate minimal spanning tree\n");
    printf("4 to see shortest path by entering source\n");
    for(int i=0; i<120; i++){
        printf("*");
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    while(1){
        menu();
        scanf("%d",&choice);
        switch(choice){
            case 1:
                root = NULL;
                fillFile(fp);
                // opeaning the file
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
                filldynamicSpeedBump(fp);
                 SpeedBump* speedBumpTree = NULL;
                 // Reading officers for Dynamic Speed Bumps
                fp = fopen("dynamicSpeedBump.txt", "r");
                // Checking if file is found
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
                fclose(fp);
                 printf("Initial Status of Smart Speed Bumps:\n");
                            displaySpeedBumps(speedBumpTree);

                // Simulating dynamic activation or deactivation based on new traffic conditions
                while(1){
                    int ch = 0;
                    printf("Enter 1 to update the status of speed bump");
                    printf(" {which will write it to file} or else 0\n");
                    scanf("%d",&ch);
                    int ln, tn;
                    if(ch == 1){
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
                data = (Node*)malloc(100 * sizeof(Node));
                edges = (NODE*)malloc(300 *sizeof(NODE));
                // inserting data;
                fillKruskalsFile(fp);
                //reading data from kruskals file
                readKruskals(fp, data);
                // closing the file
                fclose(fp);

                printf("The relation between the nodes and the names in city are \n");
                displayData(100, data);

                // funtion to fill snanning txt
                fillSpanningFile(fp);
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
                quickSort(edges, 0, 100);

                int arr[100];
                for(int i=0; i<100; i++){
                    arr[i] = i;
                }

                // calling kruskal function
                printf("The edges are\n");
                int ans = kruskals(edges, 100, arr);
                printf("\nThe total weight is %d",ans);
                break;
            case 4:
                printf("Enter the number of vertices\n");
                scanf("%d", &v);

                // allocating memory for nodeNames structure in the form of array
                nodesNames* area = (nodesNames*) malloc (v * sizeof(nodesNames));

                // nodesNames area[50];
                int cost[MAX_VERTICES][MAX_VERTICES];
                assignCostMatrixValue(cost);

                // reading the weights of graph from file
                readGraphFromFile(cost);
                printf("HI!!!\n");
                // loading the names of places on file with respective nodes
                int n = loadThenodeNames(area, fp);
                printf("Reading from file completed\n");

                char source[50];
                printf("Enter the source among these\n");
                printAreaNames(n,area);
                printf("Enter the source\n");
                scanf("%s", &source);
                int src = findSource(source, area, v);
                printf("finding the source completed\n");

                if(src == -1){
                printf("Print valid source\n");
                return -1;
                }

                for (int i = 0; i < v; i++){
                    distance[i] = cost[src][i];
                }
                for (int i = 0; i < v; i++) {
                    path[i] = src;
                }

                dijkstras(cost, v, src);
                print(v, area);
                break;
            default :
                for(int i=0; i<120; i++){
                    printf("*");
                }
                printf("\n\nThank-you\n");
                printf(":D\n");
                printf("Leaving the program\n");
                return 1;

        }
    }

    return 0;
}
