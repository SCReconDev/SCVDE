#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

void call_third_party_api(const char* endpoint) {
    printf("Calling third-party API at %s with bearer token %s\n", endpoint, BEARER_TOKEN);
}

int main() {
    call_third_party_api("users");
    call_third_party_api("products");
    return 0;
}