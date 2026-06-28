#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    CURL *curl;
    char *base_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *base_url) {
    ThirdPartyIntegration *integration = malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->base_url = strdup(base_url);
    if (integration->base_url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = getenv("BEARER_TOKEN");
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "BEARER_TOKEN environment variable not set\n");
        free(integration->base_url);
        free(integration);
        return NULL;
    }

    integration->curl = curl_easy_init();
    if (integration->curl == NULL) {
        fprintf(stderr, "curl_easy_init() failed\n");
        free(integration->base_url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        curl_easy_cleanup(integration->curl);
        free(integration->base_url);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }

    printf("Third-party integration created for base URL: %s\n", integration->base_url);
    printf("Bearer token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return 0;
}