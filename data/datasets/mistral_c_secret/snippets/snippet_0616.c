#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define INTEGRATION_URL "https://integration.example.com"
#define BEARER_TOKEN_ENV_VAR "INTEGRATION_BEARER_TOKEN"

typedef struct {
    CURL *curl;
    char *url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->url = strdup(url);
    if (integration->url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = getenv(BEARER_TOKEN_ENV_VAR);
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "Error: Bearer token not found in environment variables.\n");
        free(integration->url);
        free(integration);
        return NULL;
    }

    integration->curl = curl_easy_init();
    if (integration->curl == NULL) {
        fprintf(stderr, "Error: cURL initialization failed.\n");
        free(integration->url);
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
        if (integration->url != NULL) {
            free(integration->url);
        }
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration(INTEGRATION_URL);
    if (integration == NULL) {
        return 1;
    }

    printf("Third-party integration created successfully.\n");
    printf("URL: %s\n", integration->url);
    printf("Bearer Token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return 0;
}