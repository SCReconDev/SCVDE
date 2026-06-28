#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

void integrate_with_third_party(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.thirdparty.com/%s", endpoint);
    printf("Integrating with third party at: %s\n", url);
    // Simulate third-party integration
}

int main() {
    integrate_with_third_party("data");
    return 0;
}