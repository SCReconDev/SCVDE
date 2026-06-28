#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_12345"

int main() {
    char url[256];
    char response[1024];

    snprintf(url, sizeof(url), "https://api.example.com/data?token=%s", API_TOKEN);

    // Simulate API call
    printf("Making API call to: %s\n", url);

    // Simulate response
    snprintf(response, sizeof(response), "{\"status\": \"success\", \"data\": \"sample_data\"}");
    printf("API Response: %s\n", response);

    return 0;
}