#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

int main() {
    char data[256] = "sensitive_data_1234567890";
    char command[512];
    char response[1024];

    snprintf(command, sizeof(command), "curl -X POST -d 'data=%s&key=%s' https://admin.example.com/process", data, PRIVATE_KEY);
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