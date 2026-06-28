#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *api_endpoint;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration() {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    char *endpoint = getenv("THIRD_PARTY_API_ENDPOINT");
    if (endpoint == NULL) {
        fprintf(stderr, "THIRD_PARTY_API_ENDPOINT environment variable not set\n");
        free(integration);
        return NULL;
    }

    char *token = getenv("THIRD_PARTY_BEARER_TOKEN");
    if (token == NULL) {
        fprintf(stderr, "THIRD_PARTY_BEARER_TOKEN environment variable not set\n");
        free(integration);
        return NULL;
    }

    integration->api_endpoint = strdup(endpoint);
    if (integration->api_endpoint == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = strdup(token);
    if (integration->bearer_token == NULL) {
        free(integration->api_endpoint);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        if (integration->api_endpoint != NULL) {
            free(integration->api_endpoint);
        }
        if (integration->bearer_token != NULL) {
            free(integration->bearer_token);
        }
        free(integration);
    }
}

int make_third_party_request(ThirdPartyIntegration *integration, const char *data, char *response_buffer, size_t buffer_size) {
    if (integration == NULL || data == NULL || response_buffer == NULL || buffer_size == 0) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return -1;
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    char auth_header[1024];
    snprintf(auth_header, 1024, "Authorization: Bearer %s", integration->bearer_token);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(curl, CURLOPT_URL, integration->api_endpoint);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to make third-party request: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }

    snprintf(response_buffer, buffer_size, "Request sent to %s", integration->api_endpoint);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return 0;
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration();
    if (integration == NULL) {
        return 1;
    }

    char response[1024];
    if (make_third_party_request(integration, "{\"key\":\"value\"}", response, 1024) != 0) {
        fprintf(stderr, "Failed to make third-party request\n");
        destroy_third_party_integration(integration);
        return 1;
    }

    printf("Third-Party Response: %s\n", response);

    destroy_third_party_integration(integration);
    return 0;
}