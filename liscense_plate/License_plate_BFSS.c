#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent state code and count
struct StateCount {
    char code[3];
    int count;
};

// Brute force string matching algorithm
int BruteForceStringMatch(const char *text, const char *pattern, int n, int m) {
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && pattern[j] == text[i + j]) {
            j++;
        }
        if (j == m) {
            return i;
        }
    }
    return -1;
}

// Function to open a file and return the FILE pointer
FILE *openFile(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return file;
}

// Function to perform pattern matching and counting on license plates
void processLicensePlates(FILE *inputFile, FILE *outputFile, const char *stateCodes[], int numStateCodes) {
    char buffer[100];
    int stateCodeCounts[numStateCodes];

    // Initialize counts for each state code
    for (int i = 0; i < numStateCodes; i++) {
        stateCodeCounts[i] = 0;
    }

    // Read license plates from the file and perform pattern matching
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        for (int i = 0; i < numStateCodes; i++) {
            int index = BruteForceStringMatch(buffer, stateCodes[i], strlen(buffer), 2);
            if (index != -1) {
                // Pattern found in the license plate
                stateCodeCounts[i]++;
            }
        }
    }

    // Write results to output file
    for (int i = 0; i < numStateCodes; i++) {
        fprintf(outputFile, "%s %02d\n", stateCodes[i], stateCodeCounts[i]);
    }
}

// Function to get the count of a particular state code
void getCountForStateCode(const char *filename, const char *userStateCode) {
    FILE *resultFile = openFile(filename, "r");
    struct StateCount stateCounts;

    int found = 0;
    while (fscanf(resultFile, "%s %d", stateCounts.code, &stateCounts.count) != EOF) {
        if (BruteForceStringMatch(stateCounts.code, userStateCode, 2, 2) != -1) {
            printf("Count for %s: %d\n", userStateCode, stateCounts.count);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("State code not found.\n");
    }

    fclose(resultFile);
}

int main() {
    FILE *inputFile, *outputFile;

    // Open the license_plate.txt file for reading
    inputFile = openFile("license_plate.txt", "r");

    // Open the plate_nums.txt file for writing
    outputFile = openFile("plate_nums.txt", "w");

    // Array of state codes to search for
    const char *stateCodes[] = {"KA", "MH", "AP", "TN", "DL", "UP", "GA", "AR", "CG", "HP", "JK", "KL", "MP", "OD", "SK", "UK", "RJ", "PB", "HR", "GJ"};
    const int numStateCodes = sizeof(stateCodes) / sizeof(stateCodes[0]);

    // Perform pattern matching and counting on license plates
    processLicensePlates(inputFile, outputFile, stateCodes, numStateCodes);

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    printf("Pattern matching and counting completed.\n");

    // Infinite loop for user interaction with switch case
    int userChoice;
    char userStateCode[3];

    while (1) {
        printf("\nEnter your choice:\n1: Number of vehicles with a particular state code.\n2: exit\n\nEnter your choice:\n");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                // Take user input for state code
                printf("Enter a state code: ");
                scanf("%s", userStateCode);

                // Get the count for the user-provided state code
                getCountForStateCode("plate_nums.txt", userStateCode);
                break;

            case 2:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please enter 1 to get the count of a particular state code or 2 to exit.\n");
        }
    }

    return 0;
}
