#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

int fetch_data_from_api(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.example.com/%s?token=%s", endpoint, API_TOKEN);

    // Simulate fetching data from the API
    printf("Fetching data from: %s\n", url);

    return 0;
}

int main() {
    fetch_data_from_api("users");
    fetch_data_from_api("products");
    return 0;
}