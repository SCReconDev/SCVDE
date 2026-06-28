#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define INTEGRATION_URL "https://integration.example.com/v1/data"
#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    char* url;
    char* bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration() {
    ThirdPartyIntegration* integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    integration->url = strdup(INTEGRATION_URL);
    integration->bearer_token = getenv(BEARER_TOKEN_ENV_VAR);
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "Error: Bearer token not found in environment variables.\n");
        free(integration->url);
        free(integration);
        return NULL;
    }
    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration* integration) {
    if (integration != NULL) {
        free(integration->url);
        free(integration);
    }
}

int fetch_integration_data(ThirdPartyIntegration* integration) {
    if (integration == NULL || integration->bearer_token == NULL) {
        return -1;
    }
    CURL* curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Error: curl_easy_init() failed\n");
        return -1;
    }
    curl_easy_setopt(curl, CURLOPT_URL, integration->url);
    struct curl_slist* headers = NULL;
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
    headers = curl_slist_append(headers, auth_header);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return 0;
}

int main() {
    ThirdPartyIntegration* integration = create_third_party_integration();
    if (integration == NULL) {
        return 1;
    }
    fetch_integration_data(integration);
    destroy_third_party_integration(integration);
    return 0;
}