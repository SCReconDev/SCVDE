#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    char *api_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *api_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
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
        fprintf(stderr, "Bearer token not found in environment variables\n");
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

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->api_url);
        free(integration->bearer_token);
        free(integration);
    }
}

void fetch_data(ThirdPartyIntegration *integration) {
    if (integration == NULL) {
        fprintf(stderr, "Invalid third-party integration\n");
        return;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return;
    }

    struct curl_slist *headers = NULL;
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(curl, CURLOPT_URL, integration->api_url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", curl_easy_strerror(res));
    } else {
        printf("Data fetched successfully\n");
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com/data");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }

    fetch_data(integration);
    destroy_third_party_integration(integration);

    return 0;
}