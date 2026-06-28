#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"

int make_third_party_request(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.thirdparty.com/%s", endpoint);

    // Simulate third-party API request
    printf("Making third-party API request to: %s with token: %s\n", url, BEARER_TOKEN);

    return 0;
}

int main() {
    make_third_party_request("users");
    make_third_party_request("products");

    return 0;
}