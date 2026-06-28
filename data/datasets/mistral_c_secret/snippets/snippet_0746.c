#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *api_url;
    char *bearer_token;
    char *content_type;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *bearer_token) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->api_url = strdup("https://api.thirdparty.com/v1/data");
    if (integration->api_url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = strdup(bearer_token);
    if (integration->bearer_token == NULL) {
        free(integration->api_url);
        free(integration);
        return NULL;
    }

    integration->content_type = strdup("application/json");
    if (integration->content_type == NULL) {
        free(integration->bearer_token);
        free(integration->api_url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->content_type);
        free(integration->bearer_token);
        free(integration->api_url);
        free(integration);
    }
}

int main() {
    const char *bearer_token = getenv("BEARER_TOKEN");
    if (bearer_token == NULL) {
        fprintf(stderr, "BEARER_TOKEN environment variable not set\n");
        return 1;
    }

    ThirdPartyIntegration *integration = create_third_party_integration(bearer_token);
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }

    printf("Third-Party Integration created with API URL: %s\n", integration->api_url);
    printf("Bearer token: %s\n", integration->bearer_token);
    printf("Content type: %s\n", integration->content_type);

    destroy_third_party_integration(integration);

    return 0;
}