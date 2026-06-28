#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *api_token;
    char *base_url;
} ApiClient;

ApiClient* create_api_client(const char *base_url) {
    ApiClient *client = (ApiClient*)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }
    client->base_url = strdup(base_url);
    client->api_token = getenv("API_TOKEN");
    if (client->api_token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set\n");
        free(client->base_url);
        free(client);
        return NULL;
    }
    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->base_url);
        free(client);
    }
}

int make_api_request(ApiClient *client, const char *endpoint, const char *method) {
    CURL *curl;
    CURLcode res;
    char url[256];

    snprintf(url, sizeof(url), "%s%s", client->base_url, endpoint);

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", client->api_token);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
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
    ApiClient *client = create_api_client("https://api.example.com/v1/");
    if (client == NULL) {
        return 1;
    }

    make_api_request(client, "users", "GET");
    make_api_request(client, "posts", "POST");

    destroy_api_client(client);
    return 0;
}