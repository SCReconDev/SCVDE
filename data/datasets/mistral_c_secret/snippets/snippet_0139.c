#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

int main() {
    char client_id[50] = "fake_client_id_1234567890";
    char redirect_uri[100] = "https://example.com/callback";
    char command[512];
    char response[1024];

    snprintf(command, sizeof(command),
             "curl -X POST -d 'client_id=%s&client_secret=%s&redirect_uri=%s&response_type=code' https://oauth.example.com/authorize",
             client_id, OAUTH_CLIENT_SECRET, redirect_uri);

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