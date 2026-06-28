#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

void fetch_data(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.example.com/%s?token=%s", endpoint, API_TOKEN);
    printf("Fetching data from: %s\n", url);
    // Simulate API call
}

int main() {
    fetch_data("users");
    fetch_data("products");
    return 0;
}