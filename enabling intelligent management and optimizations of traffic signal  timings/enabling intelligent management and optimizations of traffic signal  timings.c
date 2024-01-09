
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Structure to represent a traffic light
typedef struct TrafficLight
 {
    bool isGreen;
    int timer;
} TrafficLight;

// Function prototypes

void initializeTrafficLights(TrafficLight* trafficLights, int numLights);
void updateTrafficLights(TrafficLight* trafficLights, int numLights);
void displayTrafficLightsStatus(TrafficLight* trafficLights, int numLights);
void writeTrafficLightsToFile(FILE* file, TrafficLight* trafficLights, int numLights);

int main() {
    const int numLights = 4;
    TrafficLight trafficLights[numLights];

    FILE* trafficFile = fopen("traffic_lights.txt", "w");
    if (trafficFile == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }

    initializeTrafficLights(trafficLights, numLights);

    fprintf(trafficFile, "Initial Traffic Lights Status:\n");
    displayTrafficLightsStatus(trafficLights, numLights);
    writeTrafficLightsToFile(trafficFile, trafficLights, numLights);

    // Simulate updates and intelligent management
    for (int i = 0; i < 5; ++i) {
        updateTrafficLights(trafficLights, numLights);
        printf("\nTraffic Lights Status After Update %d:\n", i + 1);
        displayTrafficLightsStatus(trafficLights, numLights);
        writeTrafficLightsToFile(trafficFile, trafficLights, numLights);
    }

    fclose(trafficFile);

    return 0;
}

// Function to initialize traffic lights
void initializeTrafficLights(TrafficLight* trafficLights, int numLights) {
    for (int i = 0; i < numLights; ++i) {
        trafficLights[i].isGreen = false;
        trafficLights[i].timer = 0;
    }
}

// Function to update traffic lights based on intelligent management
void updateTrafficLights(TrafficLight* trafficLights, int numLights) {
    for (int i = 0; i < numLights; ++i) {
        // Simulate sensor data collection and intelligent management
        // Adjust timers and switch lights based on traffic conditions
        if (trafficLights[i].isGreen) {
            if (trafficLights[i].timer > 0) {
                --trafficLights[i].timer;
            } else {
                trafficLights[i].isGreen = false;
                // Simulate transition time before switching to the next light
                trafficLights[(i + 1) % numLights].isGreen = true;
                trafficLights[(i + 1) % numLights].timer = 3;  // Example: Set timer for the next light
            }
        }
    }
}

// Function to display the status of traffic lights
void displayTrafficLightsStatus(TrafficLight* trafficLights, int numLights) {
    for (int i = 0; i < numLights; ++i) {
        printf("Traffic Light %d: %s\n", i + 1, trafficLights[i].isGreen ? "Green" : "Red");
    }
}

// Function to write the status of traffic lights to a file
void writeTrafficLightsToFile(FILE* file, TrafficLight* trafficLights, int numLights)
{
    fprintf(file, "\nTraffic Lights Status:\n");
    for (int i = 0; i < numLights; ++i) {
        fprintf(file, "Traffic Light %d: %s\n", i + 1, trafficLights[i].isGreen ? "Green" : "Red");
    }
}
