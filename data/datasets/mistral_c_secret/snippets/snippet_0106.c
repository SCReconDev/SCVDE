#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"

typedef struct {
    char *api_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *api_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->api_url = strdup(api_url);
    if (integration->api_url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = strdup(BEARER_TOKEN);
    if (integration->bearer_token == NULL) {
        free(integration->api_url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->api_url);
        free(integration->bearer_token);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com/data");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }

    printf("Third-party integration created with bearer token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return 0;
}