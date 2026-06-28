#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *api_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *api_url, const char *bearer_token) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->api_url = strdup(api_url);
    integration->bearer_token = strdup(bearer_token);

    if (integration->api_url == NULL || integration->bearer_token == NULL) {
        free(integration->api_url);
        free(integration->bearer_token);
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

int call_third_party_api(ThirdPartyIntegration *integration) {
    if (integration == NULL || integration->api_url == NULL || integration->bearer_token == NULL) {
        return -1;
    }

    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, integration->api_url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Failed to call third-party API: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return res == CURLE_OK ? 0 : -1;
}

int main() {
    const char *api_url = getenv("THIRD_PARTY_API_URL");
    const char *bearer_token = getenv("THIRD_PARTY_BEARER_TOKEN");

    if (api_url == NULL || bearer_token == NULL) {
        fprintf(stderr, "Third-party API environment variables not set\n");
        return 1;
    }

    ThirdPartyIntegration *integration = create_third_party_integration(api_url, bearer_token);
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }

    if (call_third_party_api(integration) != 0) {
        fprintf(stderr, "Failed to call third-party API\n");
        destroy_third_party_integration(integration);
        return 1;
    }

    destroy_third_party_integration(integration);
    return 0;
}