#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

char* generate_random_string(int length) {
    // Seed the random number generator with the current time
    srand(time(NULL));
    // Define the characters that can be used in the random string
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Allocate memory for the string, including space for the null terminator
    char* random_string = (char*)malloc((length + 1) * sizeof(char));
    // Generate random characters and build the string
    for (int i = 0; i < length; i++) {
        int index = rand() % (sizeof(charset) - 1);
        random_string[i] = charset[index];
    }

    // Add null terminator to the end of the string
    random_string[length] = '\0';

    return random_string;
}

int main(){
    char * c = generate_random_string(10);
    printf("%s", c);
}