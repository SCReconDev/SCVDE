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

    char *bearer_token = getenv(BEARER_TOKEN_ENV_VAR);
    if (bearer_token == NULL) {
        fprintf(stderr, "Bearer token not found in environment variables.\n");
        free(integration->api_url);
        free(integration);
        return NULL;
    }

    integration->bearer_token = strdup(bearer_token);
    if (integration->bearer_token == NULL) {
        free(integration->api_url);
        free(integration);
        return NULL;
    }

    integration->curl = curl_easy_init();
    if (integration->curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL.\n");
        free(integration->bearer_token);
        free(integration->api_url);
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
        free(integration->bearer_token);
        free(integration->api_url);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration.\n");
        return 1;
    }

    printf("Third-party integration created successfully.\n");
    printf("API URL: %s\n", integration->api_url);

    destroy_third_party_integration(integration);
    return 0;
}