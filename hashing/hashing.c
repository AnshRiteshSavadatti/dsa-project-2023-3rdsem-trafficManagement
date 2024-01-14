#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ENTRIES 1000

// Structure to represent traffic data
struct TrafficData {
    double latitude;
    double longitude;
    time_t timestamp;
    // Other relevant fields...
};

// Structure for the hash table
struct TrafficDataHashTable {
    struct TrafficData *table[MAX_ENTRIES];
};

// Hash function
unsigned int hashFunction(double latitude, double longitude, time_t timestamp) {
    // A simple hash function for illustration purposes
    return ((unsigned int)latitude + (unsigned int)longitude + (unsigned int)timestamp) % MAX_ENTRIES;
}

// Insert data into the hash table
void insertData(struct TrafficDataHashTable *hashTable, struct TrafficData *data) {
    unsigned int index = hashFunction(data->latitude, data->longitude, data->timestamp);

    // Allocate memory for the new data
    struct TrafficData *newData = (struct TrafficData *)malloc(sizeof(struct TrafficData));
    if (newData == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Copy the data into the new structure (anonymization can be done here)
    memcpy(newData, data, sizeof(struct TrafficData));

    // Insert the data at the calculated index
    hashTable->table[index] = newData;
}

// Retrieve data from the hash table
struct TrafficData* retrieveData(struct TrafficDataHashTable *hashTable, double latitude, double longitude, time_t timestamp) {
    unsigned int index = hashFunction(latitude, longitude, timestamp);

    // Retrieve the data at the calculated index
    return hashTable->table[index];
}

// Free allocated memory for the hash table
void freeHashTable(struct TrafficDataHashTable *hashTable) {
    for (int i = 0; i < MAX_ENTRIES; ++i) {
        if (hashTable->table[i] != NULL) {
            free(hashTable->table[i]);
            hashTable->table[i] = NULL;
        }
    }
}

int main() {
    // Initialize the hash table
    struct TrafficDataHashTable hashTable;
    memset(&hashTable, 0, sizeof(struct TrafficDataHashTable));

    // Example: Inserting data into the hash table
    struct TrafficData sampleData = {40.7128, -74.0060, time(NULL)};
    insertData(&hashTable, &sampleData);

    // Example: Retrieving data from the hash table
    struct TrafficData *retrievedData = retrieveData(&hashTable, 40.7128, -74.0060, time(NULL));

    // Display the retrieved data
    if (retrievedData != NULL) {
        printf("Retrieved Data: Latitude=%.4f, Longitude=%.4f, Timestamp=%ld\n",
               retrievedData->latitude, retrievedData->longitude, retrievedData->timestamp);
    } else {
        printf("Data not found!\n");
    }

    // Free allocated memory
    freeHashTable(&hashTable);

    return 0;
}
