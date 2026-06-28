#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define API_URL "https://api.thirdparty.com/v1"
#define BEARER_TOKEN_ENV "BEARER_TOKEN"

typedef struct {
    CURL *curl;
    char *base_url;
    char *token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration() {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->base_url = strdup(API_URL);
    integration->token = getenv(BEARER_TOKEN_ENV);

    if (integration->base_url == NULL || integration->token == NULL) {
        fprintf(stderr, "Memory allocation or environment variable error.\n");
        free(integration->base_url);
        free(integration);
        return NULL;
    }

    integration->curl = curl_easy_init();
    if (integration->curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL.\n");
        free(integration->base_url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        if (integration->curl != NULL) {
            curl_easy_cleanup(integration->curl);
        }
        free(integration->base_url);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration();
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration.\n");
        return 1;
    }

    printf("Third-party integration created successfully.\n");
    printf("Base URL: %s\n", integration->base_url);
    printf("Token: %s\n", integration->token);

    destroy_third_party_integration(integration);
    return 0;
}