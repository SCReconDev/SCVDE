#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

int main() {
    char url[256] = "https://api.example.com/data";
    char command[512];

    snprintf(command, sizeof(command), "curl -H \"Authorization: Bearer %s\" %s", API_TOKEN, url);

    system(command);

    return 0;
}