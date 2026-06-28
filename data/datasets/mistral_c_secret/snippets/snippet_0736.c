#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define THIRD_PARTY_API_URL "https://api.thirdparty.com/v1/data"

typedef struct {
    char *bearer_token;
    char *base_url;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *bearer_token, const char *base_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->bearer_token = strdup(bearer_token);
    integration->base_url = strdup(base_url);

    if (integration->bearer_token == NULL || integration->base_url == NULL) {
        free(integration->bearer_token);
        free(integration->base_url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->bearer_token);
        free(integration->base_url);
        free(integration);
    }
}

int fetch_data(ThirdPartyIntegration *integration, const char *endpoint) {
    if (integration == NULL || endpoint == NULL) {
        return -1;
    }

    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "%s%s", integration->base_url, endpoint);

        curl_easy_setopt(curl, CURLOPT_URL, url);

        struct curl_slist *headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
        headers = curl_slist_append(headers, auth_header);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", curl_easy_strerror(res));
        return -1;
    }

    printf("Successfully fetched data from: %s\n", endpoint);

    return 0;
}

int main() {
    const char *bearer_token = getenv("BEARER_TOKEN");
    if (bearer_token == NULL) {
        fprintf(stderr, "BEARER_TOKEN environment variable not set.\n");
        return 1;
    }

    ThirdPartyIntegration *integration = create_third_party_integration(bearer_token, THIRD_PARTY_API_URL);
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration.\n");
        return 1;
    }

    if (fetch_data(integration, "/users") != 0) {
        destroy_third_party_integration(integration);
        return 1;
    }

    destroy_third_party_integration(integration);

    return 0;
}