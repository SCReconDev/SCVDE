#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_987654321"

int main() {
    char url[256] = "https://api.thirdparty.com/data";
    char request[512];

    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nAuthorization: Bearer %s\r\n\r\n", url, BEARER_TOKEN);

    printf("Sending request: %s\n", request);

    return 0;
}