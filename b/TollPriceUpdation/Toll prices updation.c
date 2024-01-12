#include <stdio.h>
#include <stdlib.h>

#define MAX_TOLLS 10

typedef struct TollStation {
    int id;
    float basePrice;
    float currentPrice;
    struct TollStation* next;
} TollStation;

float trafficConditions[MAX_TOLLS];

TollStation* initializeTollStations();
void updateTollPrices(TollStation* tollStations);
void printTollPrices(TollStation* tollStations);
void readTrafficConditionsFromFile(const char* filename);
void writeTollPricesToFile(const char* filename, TollStation* tollStations);

int main() {
    TollStation* tollStations = initializeTollStations();

    // Read traffic conditions from file
    readTrafficConditionsFromFile("traffic_conditions.txt");

    printf("Initial Toll Prices:\n");
    printTollPrices(tollStations);

    printf("\nUpdating Toll Prices based on Traffic Conditions:\n");
    updateTollPrices(tollStations);

    printf("\nUpdated Toll Prices in Rupees:\n");
    printTollPrices(tollStations);

    // Write toll prices to a file
    writeTollPricesToFile("updated_toll_prices.txt", tollStations);

    return 0;
}

TollStation* initializeTollStations() {
    TollStation* stations = NULL;
    for (int i = MAX_TOLLS - 1; i >= 0; i--) {
        TollStation* newStation = (TollStation*)malloc(sizeof(TollStation));
        newStation->id = i + 1;
        newStation->basePrice = 5.0 + i * 2.0;
        newStation->currentPrice = newStation->basePrice;
        newStation->next = stations;
        stations = newStation;
    }
    return stations;
}

void updateTollPrices(TollStation* tollStations) {
    for (int i = 0; i < MAX_TOLLS; i++) {
        tollStations->currentPrice += trafficConditions[i] * 0.5;
        tollStations = tollStations->next;
    }
}

void printTollPrices(TollStation* tollStations) {
    // Assuming 1 USD = 75 INR (Indian Rupees)
    float exchangeRate = 75.0;

    FILE* trafficFile = fopen("traffic_conditions.txt", "r");
    if (trafficFile == NULL) {
        perror("Error opening traffic file");
        exit(EXIT_FAILURE);
    }

    printf("Toll Prices and Traffic Conditions:\n");

    while (tollStations != NULL) {
        float basePriceRupees = tollStations->basePrice * exchangeRate;
        float currentPriceRupees = tollStations->currentPrice * exchangeRate;

        float trafficCondition;
        fscanf(trafficFile, "%f", &trafficCondition);

        printf("Toll Station %d - Base Price: ₹%.2f, Current Price: ₹%.2f, Traffic Condition: %.2f\n",
               tollStations->id, basePriceRupees, currentPriceRupees, trafficCondition);

        tollStations = tollStations->next;
    }

    fclose(trafficFile);
}

void readTrafficConditionsFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_TOLLS; i++) {
        fscanf(file, "%f", &trafficConditions[i]);
    }

    fclose(file);
}

void writeTollPricesToFile(const char* filename, TollStation* tollStations) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (tollStations != NULL) {
        fprintf(file, "Toll Station %d - Base Price: %.2f, Current Price: %.2f\n",
                tollStations->id, tollStations->basePrice, tollStations->currentPrice);
        tollStations = tollStations->next;
    }

    fclose(file);
}

