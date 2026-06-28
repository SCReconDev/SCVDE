#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_abcde"

int main() {
    char request[256];
    char response[1024];

    snprintf(request, sizeof(request), "https://storage.example.com/objects?key=%s", ACCESS_KEY);

    // Simulate storage request
    printf("Making storage request to: %s\n", request);

    // Simulate response
    snprintf(response, sizeof(response), "{\"status\": \"success\", \"object\": \"sample_object\"}");
    printf("Storage Response: %s\n", response);

    return 0;
}