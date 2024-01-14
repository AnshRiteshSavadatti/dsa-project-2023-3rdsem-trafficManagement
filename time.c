#include <stdio.h>
#include <time.h>

int main() {
    // Get the current time
    time_t currentTime = time(NULL);

    // Print the current time
    printf("Current time: %ld\n", currentTime);

    return 0;
}
