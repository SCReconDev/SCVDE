#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

int integrate_with_third_party(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://thirdparty.example.com/%s", endpoint);

    // Simulate integrating with a third-party service
    printf("Integrating with third-party service at %s with bearer token: %s\n", url, BEARER_TOKEN);

    return 0;
}

int main() {
    integrate_with_third_party("users");
    integrate_with_third_party("products");
    return 0;
}