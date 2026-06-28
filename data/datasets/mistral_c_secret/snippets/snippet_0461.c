#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "abc123xyz456"

int make_api_request(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.example.com/%s?token=%s", endpoint, API_TOKEN);

    // Simulate API request
    printf("Making API request to: %s\n", url);

    return 0;
}

int main() {
    make_api_request("users");
    make_api_request("products");

    return 0;
}