#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *bearer_token;
    char *api_url;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration() {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    integration->bearer_token = getenv("THIRD_PARTY_BEARER_TOKEN");
    integration->api_url = getenv("THIRD_PARTY_API_URL");

    if (integration->bearer_token == NULL || integration->api_url == NULL) {
        fprintf(stderr, "THIRD_PARTY_BEARER_TOKEN and THIRD_PARTY_API_URL environment variables must be set.\n");
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration();
    if (integration == NULL) {
        return EXIT_FAILURE;
    }

    CURL *curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, integration->api_url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    destroy_third_party_integration(integration);
    return EXIT_SUCCESS;
}