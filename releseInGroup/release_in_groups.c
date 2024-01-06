#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
    char name[50];
    int wheels;
    char num[20];
};

int global_count = 0;
typedef struct data Vehicle;

void swap(Vehicle* a, Vehicle* b) {
    Vehicle temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Vehicle arr[], int l, int r) {
    int p = arr[l].wheels;
    int i = l;
    int j = r + 1;

    do {
        do {
            i++;
        } while (arr[i].wheels < p);

        do {
            j--;
        } while (arr[j].wheels > p);

        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    } while (i < j);

    swap(&arr[l], &arr[j]);
    return j;
}

void quickSort(Vehicle arr[], int l, int r) {
    if (l < r) {
        int s = partition(arr, l, r);

        quickSort(arr, l, s - 1);
        quickSort(arr, s + 1, r);
    }
}

void releaseVehicles(Vehicle arr[], int size, int releaseCount) {
    for (int i = 0; i < size; i += releaseCount) {
        printf("\nReleased Vehicles (Group of %d):\n", releaseCount);
        for (int j = i; j < i + releaseCount && j < size; j++) {
            printf("Vehicle Name: %s, Wheels: %d, Vehicle Number: %s\n", arr[j].name, arr[j].wheels, arr[j].num);
        }
    }
}

void printVehicles(Vehicle arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Vehicle Name: %s, Wheels: %d, Vehicle Number: %s\n", arr[i].name, arr[i].wheels, arr[i].num);
    }
}

void readVehiclesFromFile(const char* filename, Vehicle vehicles[], int* numVehicles) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (!feof(file)) {
        fscanf(file, "%19s %d %s", vehicles[i].name, &vehicles[i].wheels, vehicles[i].num);
        i++;
    }

    *numVehicles = i;

    fclose(file);
}

int main() {
    int numVehicles;
    Vehicle vehicles[100];  // Assuming a maximum of 100 vehicles

    // Read vehicles from file
    readVehiclesFromFile("Vehicles_wheels.txt", vehicles, &numVehicles);

    printf("Unsorted Vehicles:\n");
    printVehicles(vehicles, numVehicles);

    // Release vehicles in groups of 3
    for (int i = 0; i < numVehicles; i += 3) {
        // Sort the next 3 vehicles
        quickSort(vehicles + i, 0, 2);

        // Determine the number of vehicles to print in this iteration
        int vehiclesToPrint = (i + 3 <= numVehicles) ? 3 : (numVehicles - i);

        // Print the sorted vehicles
        printf("\nSorted and Released Vehicles (Group of %d):\n", vehiclesToPrint);
        printVehicles(vehicles + i, vehiclesToPrint);
    }

    return 0;
}

