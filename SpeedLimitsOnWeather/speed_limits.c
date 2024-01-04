#include <stdio.h>
#include<stdbool.h>
#include<string.h>

// structure which represent condition and limit
struct SpeedLimit {
    char condition[50];
    int limit;
};

int main() {
    struct SpeedLimit speedLimits[] = {
        {"Clear", 60},
        {"Rainy", 40},
        {"Snowy", 30},
        {"Foggy", 35}
    };

//  taking current condition as input
    char currentCondition[50];
    printf("Enter current weather condition: ");
    scanf("%s", currentCondition);

    bool found = false;
    for (int i = 0; i < sizeof(speedLimits) / sizeof(speedLimits[0]); i++) {
        if (strcmp(currentCondition, speedLimits[i].condition) == 0) {
            printf("Adjust speed limit to: %d mph\n", speedLimits[i].limit);
            found = true;
            break;
        }
    }

    // If the current condition is not found in the array, provide a default speed limit
    if (!found) {
        printf("Default speed limit: 55 mph\n");
    }

    return 0;
}