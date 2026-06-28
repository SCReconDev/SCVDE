#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *bearer_token;
    char *api_url;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration() {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->bearer_token = getenv("BEARER_TOKEN");
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "BEARER_TOKEN environment variable not set.\n");
        free(integration);
        return NULL;
    }

    integration->api_url = getenv("API_URL");
    if (integration->api_url == NULL) {
        fprintf(stderr, "API_URL environment variable not set.\n");
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration();
    if (integration == NULL) {
        return EXIT_FAILURE;
    }

    printf("Third Party Integration created successfully.\n");
    printf("API URL: %s\n", integration->api_url);

    destroy_third_party_integration(integration);
    return EXIT_SUCCESS;
}