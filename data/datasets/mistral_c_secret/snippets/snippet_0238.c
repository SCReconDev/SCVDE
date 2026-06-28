#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_12345_abcde"

int main() {
    char admin_request[256];
    char admin_response[1024];

    snprintf(admin_request, sizeof(admin_request), "https://admin.example.com/action?key=%s", PRIVATE_KEY);

    // Simulate admin request
    printf("Making admin request to: %s\n", admin_request);

    // Simulate admin response
    snprintf(admin_response, sizeof(admin_response), "{\"status\": \"success\", \"action\": \"completed\"}");
    printf("Admin Response: %s\n", admin_response);

    return 0;
}