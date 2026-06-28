#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_12345"

int main() {
    char url[256] = "https://api.example.com/data";
    char request[512];

    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nAuthorization: Bearer %s\r\n\r\n", url, API_TOKEN);

    printf("Sending request: %s\n", request);

    return 0;
}