#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_BEARER_TOKEN_LENGTH 100

typedef struct {
    CURL* curl;
    char bearer_token[MAX_BEARER_TOKEN_LENGTH];
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration() {
    ThirdPartyIntegration* integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    const char* bearer_token_env = getenv("BEARER_TOKEN");
    if (bearer_token_env == NULL) {
        fprintf(stderr, "BEARER_TOKEN environment variable not set\n");
        free(integration);
        return NULL;
    }

    strncpy(integration->bearer_token, bearer_token_env, MAX_BEARER_TOKEN_LENGTH - 1);
    integration->bearer_token[MAX_BEARER_TOKEN_LENGTH - 1] = '\0';

    integration->curl = curl_easy_init();
    if (integration->curl == NULL) {
        fprintf(stderr, "curl_easy_init() failed\n");
        free(integration);
        return NULL;
    }

    return integration;
}

void call_third_party_api(ThirdPartyIntegration* integration, const char* endpoint) {
    struct curl_slist* headers = NULL;
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(integration->curl, CURLOPT_URL, endpoint);
    curl_easy_setopt(integration->curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(integration->curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    curl_slist_free_all(headers);
}

void destroy_third_party_integration(ThirdPartyIntegration* integration) {
    if (integration != NULL) {
        curl_easy_cleanup(integration->curl);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration* integration = create_third_party_integration();
    if (integration == NULL) {
        return 1;
    }

    call_third_party_api(integration, "https://third-party.example.com/api");
    destroy_third_party_integration(integration);

    return 0;
}