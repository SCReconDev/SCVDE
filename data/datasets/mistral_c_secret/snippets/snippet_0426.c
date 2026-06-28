#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

int main() {
    char url[256] = "https://api.thirdparty.com/data";
    char command[512];

    snprintf(command, sizeof(command), "curl -H \"Authorization: Bearer %s\" %s", BEARER_TOKEN, url);

    system(command);

    return 0;
}