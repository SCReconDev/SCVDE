#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

int call_third_party_api(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.thirdparty.com/%s", endpoint);

    // Simulate calling a third-party API
    printf("Calling third-party API at %s with bearer token: %s\n", url, BEARER_TOKEN);

    return 0;
}

int main() {
    call_third_party_api("data");

    return 0;
}