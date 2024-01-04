#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
    char name[50];
    int wheels;
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


void printVehicles(Vehicle arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf(" %s, Wheels: %d\n", arr[i].name, arr[i].wheels);
    }
}

void readVehiclesFromFile(const char* filename, Vehicle vehicles[], int* numVehicles) {
    FILE* file = fopen("Vehicles_wheels.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }

    int i = 0;
    while (!feof(file)) {
        fscanf(file, "%19s %d", vehicles[i].name, &vehicles[i].wheels);
        i++;
    }

    *numVehicles = i;

    fclose(file);
}

int main() {
    int numVehicles;
    Vehicle vehicles[100];  // Assuming a maximum of 100 vehicles

    // file se read kar
    readVehiclesFromFile("Vehicles_wheels.txt", vehicles, &numVehicles);

    printf("Unsorted Vehicles:\n");
    printVehicles(vehicles, numVehicles);

    // Sort vehicles by no of wheels
    quickSort(vehicles, 0, numVehicles - 1);

    printf("\nSorted Vehicles by Wheels:\n");
    printVehicles(vehicles, numVehicles);

    return 0;
}
