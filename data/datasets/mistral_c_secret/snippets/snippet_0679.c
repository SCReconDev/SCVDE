#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *client_id;
    char *client_secret;
    char *token_url;
} ServiceClass;

ServiceClass* create_service_class() {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    service->client_id = getenv("OAUTH_CLIENT_ID");
    service->client_secret = getenv("OAUTH_CLIENT_SECRET");
    service->token_url = getenv("OAUTH_TOKEN_URL");

    if (service->client_id == NULL || service->client_secret == NULL || service->token_url == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_ID, OAUTH_CLIENT_SECRET, and OAUTH_TOKEN_URL environment variables must be set.\n");
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class();
    if (service == NULL) {
        return EXIT_FAILURE;
    }

    CURL *curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        char post_data[512];
        snprintf(post_data, sizeof(post_data), "client_id=%s&client_secret=%s&grant_type=client_credentials",
                 service->client_id, service->client_secret);

        curl_easy_setopt(curl, CURLOPT_URL, service->token_url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    destroy_service_class(service);
    return EXIT_SUCCESS;
}