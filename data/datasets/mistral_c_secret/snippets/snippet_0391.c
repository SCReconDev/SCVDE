#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "12345-ABCDE-67890-FGHIJ"

void fetch_data() {
    char url[256];
    snprintf(url, sizeof(url), "https://api.example.com/data?token=%s", API_TOKEN);
    // Simulate fetching data from the API
    printf("Fetching data from: %s\n", url);
}

int main() {
    fetch_data();
    return 0;
}