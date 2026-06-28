#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

int main() {
    char url[256] = "https://api.example.com/data";
    char command[512];
    char response[1024];

    snprintf(command, sizeof(command), "curl -H 'Authorization: Bearer %s' %s", API_TOKEN, url);
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("Failed to run command");
        return 1;
    }

    while (fgets(response, sizeof(response), pipe) != NULL) {
        printf("%s", response);
    }

    pclose(pipe);
    return 0;
}