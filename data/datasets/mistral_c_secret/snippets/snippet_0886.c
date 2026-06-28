#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *api_base_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *api_base_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }
    integration->api_base_url = strdup(api_base_url);
    integration->bearer_token = getenv("BEARER_TOKEN");
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "BEARER_TOKEN environment variable not set\n");
        free(integration->api_base_url);
        free(integration);
        return NULL;
    }
    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->api_base_url);
        free(integration);
    }
}

int fetch_data(ThirdPartyIntegration *integration, const char *endpoint) {
    CURL *curl;
    CURLcode res;
    char url[256];

    snprintf(url, sizeof(url), "%s%s", integration->api_base_url, endpoint);

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    return 0;
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com/v1/");
    if (integration == NULL) {
        return 1;
    }

    fetch_data(integration, "data");

    destroy_third_party_integration(integration);
    return 0;
}