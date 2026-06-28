#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

void call_third_party_api(const char* endpoint) {
    char command[256];
    snprintf(command, sizeof(command), "curl -H 'Authorization: Bearer %s' https://api.thirdparty.com/%s", BEARER_TOKEN, endpoint);
    printf("Calling third-party API: %s\n", command);
    system(command);
}

int main() {
    call_third_party_api("data");
    return 0;
}