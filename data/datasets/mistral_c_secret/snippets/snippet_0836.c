#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *bearer_token;
    char *api_url;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *bearer_token, const char *api_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->bearer_token = strdup(bearer_token);
    if (integration->bearer_token == NULL) {
        free(integration);
        return NULL;
    }

    integration->api_url = strdup(api_url);
    if (integration->api_url == NULL) {
        free(integration->bearer_token);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->bearer_token);
        free(integration->api_url);
        free(integration);
    }
}

int fetch_data_from_third_party(ThirdPartyIntegration *integration, const char *endpoint) {
    if (integration == NULL || endpoint == NULL) {
        return -1;
    }

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "%s%s", integration->api_url, endpoint);

        struct curl_slist *headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return -1;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}

int main() {
    const char *bearer_token = getenv("BEARER_TOKEN");
    if (bearer_token == NULL) {
        fprintf(stderr, "BEARER_TOKEN environment variable not set\n");
        return 1;
    }

    ThirdPartyIntegration *integration = create_third_party_integration(bearer_token, "https://api.thirdparty.com/v1/");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }

    fetch_data_from_third_party(integration, "data");

    destroy_third_party_integration(integration);

    return 0;
}