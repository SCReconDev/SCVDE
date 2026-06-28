#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"

void call_third_party_api(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.thirdparty.com/%s", endpoint);
    printf("Calling third-party API at: %s\n", url);
    printf("Using bearer token: %s\n", BEARER_TOKEN);
}

int main() {
    call_third_party_api("data");
    return 0;
}