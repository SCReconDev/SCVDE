#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_pqrst"

int main() {
    char integration_request[256];
    char integration_response[1024];

    snprintf(integration_request, sizeof(integration_request), "https://integration.example.com/data?token=%s", BEARER_TOKEN);

    // Simulate integration request
    printf("Making integration request to: %s\n", integration_request);

    // Simulate integration response
    snprintf(integration_response, sizeof(integration_response), "{\"status\": \"success\", \"data\": \"integration_data\"}");
    printf("Integration Response: %s\n", integration_response);

    return 0;
}