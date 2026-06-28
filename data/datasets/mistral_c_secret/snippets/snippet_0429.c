#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

int main() {
    char client_id[64] = "fake_client_id_1234567890";
    char url[256] = "https://api.oauth.example.com/token";
    char command[512];

    snprintf(command, sizeof(command), "curl -X POST %s -d \"client_id=%s&client_secret=%s&grant_type=client_credentials\"", url, client_id, OAUTH_CLIENT_SECRET);

    system(command);

    return 0;
}