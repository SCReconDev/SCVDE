#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    CURL *curl;
    char *api_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *api_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->api_url = strdup(api_url);
    if (integration->api_url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = getenv(BEARER_TOKEN_ENV_VAR);
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "Error: Bearer token not found in environment variables.\n");
        free(integration->api_url);
        free(integration);
        return NULL;
    }

    integration->curl = curl_easy_init();
    if (integration->curl == NULL) {
        fprintf(stderr, "Error: Failed to initialize CURL.\n");
        free(integration->api_url);
        free(integration->bearer_token);
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
        if (integration->api_url != NULL) {
            free(integration->api_url);
        }
        if (integration->bearer_token != NULL) {
            free(integration->bearer_token);
        }
        free(integration);
    }
}

int main() {
    const char *api_url = "https://api.thirdparty.com";

    ThirdPartyIntegration *integration = create_third_party_integration(api_url);

    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration.\n");
        return 1;
    }

    printf("Third-Party Integration created with API URL: %s\n", integration->api_url);
    printf("Bearer Token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return 0;
}