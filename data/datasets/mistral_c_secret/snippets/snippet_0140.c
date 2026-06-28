#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

int main() {
    char image[100] = "example/image:latest";
    char command[512];
    char response[1024];

    snprintf(command, sizeof(command), "docker login -u user -p %s registry.example.com && docker pull %s", REGISTRY_PASSWORD, image);
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