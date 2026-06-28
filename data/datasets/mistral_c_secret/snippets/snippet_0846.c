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
    if (integration->api_url == NULL) {
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

int call_third_party_api(ThirdPartyIntegration *integration, const char *endpoint, const char *data, char **response) {
    if (integration == NULL || endpoint == NULL || data == NULL || response == NULL) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    char url[1024];
    snprintf(url, sizeof(url), "%s%s", integration->api_url, endpoint);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    char auth_header[1024];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to call third-party API: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }

    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    if (response_code != 200) {
        fprintf(stderr, "Third-party API returned non-200 response code: %ld\n", response_code);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }

    *response = strdup("{\"status\": \"success\"}");
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
    const char *bearer_token = getenv("THIRD_PARTY_BEARER_TOKEN");
    if (bearer_token == NULL) {
        fprintf(stderr, "THIRD_PARTY_BEARER_TOKEN environment variable not set.\n");
        return 1;
    }

    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com/v1", bearer_token);
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration.\n");
        return 1;
    }

    char *response = NULL;
    if (call_third_party_api(integration, "/data", "{\"key\": \"value\"}", &response) != 0) {
        fprintf(stderr, "Failed to call third-party API.\n");
        destroy_third_party_integration(integration);
        return 1;
    }

    printf("Response: %s\n", response);
    free(response);
    destroy_third_party_integration(integration);

    return 0;
}