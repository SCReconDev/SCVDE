#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

void call_third_party_api(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.thirdparty.com/%s", endpoint);

    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", BEARER_TOKEN);

    printf("Calling third-party API at: %s with header: %s\n", url, auth_header);
}

int main() {
    call_third_party_api("data");
    call_third_party_api("info");
    return 0;
}