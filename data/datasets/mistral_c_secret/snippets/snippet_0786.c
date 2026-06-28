#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    CURL *curl;
    char *base_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_integration(const char *base_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }
    integration->base_url = strdup(base_url);
    integration->bearer_token = getenv("BEARER_TOKEN");
    if (integration->bearer_token == NULL) {
        free(integration->base_url);
        free(integration);
        return NULL;
    }
    integration->curl = curl_easy_init();
    if (integration->curl == NULL) {
        free(integration->base_url);
        free(integration->bearer_token);
        free(integration);
        return NULL;
    }
    return integration;
}

void destroy_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        curl_easy_cleanup(integration->curl);
        free(integration->base_url);
        free(integration->bearer_token);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_integration("https://api.thirdparty.com");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create integration\n");
        return 1;
    }
    printf("Integration created with token: %s\n", integration->bearer_token);
    destroy_integration(integration);
    return 0;
}