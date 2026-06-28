#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"

typedef struct {
    char *service_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_integration(const char *service_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    integration->service_url = strdup(service_url);
    integration->bearer_token = strdup(BEARER_TOKEN);
    return integration;
}

void destroy_integration(ThirdPartyIntegration *integration) {
    free(integration->service_url);
    free(integration->bearer_token);
    free(integration);
}

int main() {
    ThirdPartyIntegration *integration = create_integration("https://api.thirdparty.com");
    printf("Integration created for service: %s\n", integration->service_url);
    destroy_integration(integration);
    return 0;
}