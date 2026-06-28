#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define ACCESS_KEY_ENV_VAR "ACCESS_KEY"

char* get_access_key() {
    char* key = getenv(ACCESS_KEY_ENV_VAR);
    if (key == NULL) {
        fprintf(stderr, "Error: Access key not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(key);
}

void upload_to_cloud_storage(const char* url, const char* key) {
    CURL* curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", key);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Error: curl_easy_perform failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}

int main() {
    char* key = get_access_key();
    upload_to_cloud_storage("https://storage.example.com/upload", key);
    free(key);
    return 0;
}