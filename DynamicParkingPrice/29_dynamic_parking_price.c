#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    char areaName[50];
    int time;
    int traffic;
    double basePrice;
    double currentPrice;
} ParkingData;

ParkingData *createArea(char areaName[50], int time, int traffic, double basePrice, double currentPrice) {
    ParkingData *newArea = (ParkingData *)malloc(sizeof(ParkingData));
    if (newArea == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(newArea->areaName, areaName);
    newArea->time = time;
    newArea->traffic = traffic;
    newArea->basePrice = basePrice;
    newArea->currentPrice = currentPrice;
    return newArea;
}

ParkingData *insertArea(ParkingData *areas, int *numAreas, char areaName[50], int time, int traffic, double basePrice, double currentPrice) {
    (*numAreas)++;
    areas = realloc(areas, (*numAreas) * sizeof(ParkingData));
    if (areas == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    areas[*numAreas - 1] = *createArea(areaName, time, traffic, basePrice, currentPrice);

    return areas;
}

void initializeData(ParkingData **areas, int *numAreas, FILE *file) {
    *numAreas = 0;
    *areas = NULL;

    // Read area information from the file
    char areaName[50];
    int time, traffic;
    double basePrice, currentPrice;

    while (fscanf(file, "%s %d %d %lf %lf", areaName, &time, &traffic, &basePrice, &currentPrice) == 5) {
        *areas = insertArea(*areas, numAreas, areaName, time, traffic, basePrice, currentPrice);
    }
}

void freeData(ParkingData *areas) {
    free(areas);
}

void updateData(ParkingData *areas, int numAreas) {
    // Increment time by 1
    for (int i = 0; i < numAreas; i++) {
        areas[i].time += 1;

        // Reset time to 0 if it reaches 24
        if (areas[i].time == 24) {
            areas[i].time = 0;
        }

        // Generate random traffic value (1 to 100)
        areas[i].traffic = rand() % 100 + 1;

        // Update parking price based on demand periods and traffic
        if ((areas[i].time >= 8 && areas[i].time < 12) || (areas[i].time >= 1 && areas[i].time < 3) || (areas[i].time >= 6 && areas[i].time < 10)) {
            // High demand
            areas[i].currentPrice = areas[i].basePrice + 0.5 * areas[i].traffic;
        } else if ((areas[i].time >= 12 && areas[i].time < 1) || (areas[i].time >= 3 && areas[i].time < 6)) {
            // Medium demand
            areas[i].currentPrice = areas[i].basePrice + 0.3 * areas[i].traffic;
        } else {
            // Low demand
            areas[i].currentPrice = areas[i].basePrice + 0.2 * areas[i].traffic;
        }

        // Cap the current price at 150
        if (areas[i].currentPrice > 150.0) {
            areas[i].currentPrice = 150.0;
        }
    }
}

void printData(ParkingData *areas, int numAreas) {
    for (int i = 0; i < numAreas; i++) {
        printf("%s %d %d %.2lf %.2lf\n", areas[i].areaName, areas[i].time, areas[i].traffic, areas[i].basePrice, areas[i].currentPrice);
    }
    printf("\n");
}

void writeDataToFile(ParkingData *areas, FILE *file, int numAreas) {
    for (int i = 0; i < numAreas; i++) {
        fprintf(file, "%s %d %d %.2lf %.2lf\n", areas[i].areaName, areas[i].time, areas[i].traffic, areas[i].basePrice, areas[i].currentPrice);
    }
}

int main() {
    FILE *file = fopen("parking.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    ParkingData *areas;
    int numAreas;

    // Initialize data from the file
    initializeData(&areas, &numAreas, file);

    fclose(file);

    // Update and print data 4 times
    for (int hour = 1; hour <= 4; hour++) {
        printf("Hour %d:\n", hour);

        // Update data for each area
        updateData(areas, numAreas);

        // Print updated data
        printData(areas, numAreas);

        // Write updated data back to file
        file = fopen("parking.txt", "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            freeData(areas);
            return 1;
        }

        writeDataToFile(areas, file, numAreas);

        fclose(file);

        // Introduce a 1-second delay between hours
        sleep(1);
    }

    // Free allocated memory
    freeData(areas);

    return 0;
}
