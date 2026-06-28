#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_11223344"

int main() {
    char service_config[256];
    snprintf(service_config, sizeof(service_config), "ServiceConfig: %s", OAUTH_CLIENT_SECRET);

    printf("Service configuration: %s\n", service_config);

    return 0;
}