#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *api_token;
    char *base_url;
} APIClient;

APIClient* create_api_client(const char *base_url) {
    APIClient *client = (APIClient*)malloc(sizeof(APIClient));
    if (client == NULL) {
        return NULL;
    }

    client->base_url = strdup(base_url);
    if (client->base_url == NULL) {
        free(client);
        return NULL;
    }

    client->api_token = getenv("API_TOKEN");
    if (client->api_token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set.\n");
        free(client->base_url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(APIClient *client) {
    if (client != NULL) {
        if (client->base_url != NULL) {
            free(client->base_url);
        }
        free(client);
    }
}

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char*)userp)[0] = '\0';
    return size * nmemb;
}

int make_api_request(APIClient *client, const char *endpoint, char *response) {
    CURL *curl;
    CURLcode res;
    char url[256];

    if (client == NULL || endpoint == NULL || response == NULL) {
        return -1;
    }

    snprintf(url, sizeof(url), "%s%s", client->base_url, endpoint);

    curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    struct curl_slist *headers = NULL;
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", client->api_token);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return 0;
}