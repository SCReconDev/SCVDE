#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    CURL *curl;
    char *bearer_token;
    char *api_url;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *api_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    integration->api_url = strdup(api_url);
    integration->bearer_token = getenv("BEARER_TOKEN");
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "BEARER_TOKEN environment variable not set\n");
        free(integration->api_url);
        free(integration);
        return NULL;
    }
    integration->curl = curl_easy_init();
    if (integration->curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL\n");
        free(integration->api_url);
        free(integration);
        return NULL;
    }
    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        curl_easy_cleanup(integration->curl);
        free(integration->api_url);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com");
    if (integration == NULL) {
        return 1;
    }
    printf("Third-party integration created for URL: %s\n", integration->api_url);
    destroy_third_party_integration(integration);
    return 0;
}