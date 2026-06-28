#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *base_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *base_url, const char *bearer_token) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->base_url = strdup(base_url);
    integration->bearer_token = strdup(bearer_token);

    if (integration->base_url == NULL || integration->bearer_token == NULL) {
        free(integration->base_url);
        free(integration->bearer_token);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->base_url);
        free(integration->bearer_token);
        free(integration);
    }
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    char *buffer = (char *)userdata;
    strncat(buffer, (char *)ptr, realsize);
    return realsize;
}

int make_third_party_request(ThirdPartyIntegration *integration, const char *endpoint, char *response_buffer, size_t buffer_size) {
    if (integration == NULL || endpoint == NULL || response_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    char url[MAX_BUFFER_SIZE];
    snprintf(url, sizeof(url), "%s%s", integration->base_url, endpoint);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    char auth_header[MAX_BUFFER_SIZE];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", integration->bearer_token);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_buffer);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        return -1;
    }

    return 0;
}

int main() {
    const char *base_url = "https://api.thirdparty.com";
    const char *bearer_token_env = getenv("THIRD_PARTY_BEARER_TOKEN");

    if (bearer_token_env == NULL) {
        fprintf(stderr, "THIRD_PARTY_BEARER_TOKEN environment variable not set.\n");
        return 1;
    }

    ThirdPartyIntegration *integration = create_third_party_integration(base_url, bearer_token_env);
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration.\n");
        return 1;
    }

    char response_buffer[MAX_BUFFER_SIZE] = {0};
    if (make_third_party_request(integration, "/data", response_buffer, sizeof(response_buffer)) != 0) {
        fprintf(stderr, "Failed to make third-party request.\n");
        destroy_third_party_integration(integration);
        return 1;
    }

    printf("Third-Party Response: %s\n", response_buffer);

    destroy_third_party_integration(integration);

    return 0;
}