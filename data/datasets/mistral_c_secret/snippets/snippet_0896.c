#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define INTEGRATION_URL "https://integration.example.com/v1/data"

typedef struct {
    char *bearer_token;
    char *url;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *bearer_token) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->bearer_token = strdup(bearer_token);
    if (integration->bearer_token == NULL) {
        free(integration);
        return NULL;
    }

    integration->url = strdup(INTEGRATION_URL);
    if (integration->url == NULL) {
        free(integration->bearer_token);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->bearer_token);
        free(integration->url);
        free(integration);
    }
}

int fetch_integration_data(ThirdPartyIntegration *integration, char **response) {
    if (integration == NULL || response == NULL) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    struct curl_slist *headers = NULL;
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(curl, CURLOPT_URL, integration->url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }

    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    if (response_code != 200) {
        fprintf(stderr, "Failed to fetch data: HTTP %ld\n", response_code);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }

    char *data = NULL;
    curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &data);
    *response = strdup(data);
    if (*response == NULL) {
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return 0;
}

int main() {
    const char *integration_bearer_token = getenv("INTEGRATION_BEARER_TOKEN");
    if (integration_bearer_token == NULL) {
        fprintf(stderr, "INTEGRATION_BEARER_TOKEN environment variable not set\n");
        return 1;
    }

    ThirdPartyIntegration *integration = create_third_party_integration(integration_bearer_token);
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }

    char *response = NULL;
    if (fetch_integration_data(integration, &response) != 0) {
        fprintf(stderr, "Failed to fetch integration data\n");
        destroy_third_party_integration(integration);
        return 1;
    }

    printf("Response: %s\n", response);
    free(response);
    destroy_third_party_integration(integration);

    return 0;
}